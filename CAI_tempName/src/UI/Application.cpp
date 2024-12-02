#include "caipch.h"
#include "Application.h"
#include "UIElement.h"
#include "Controls/ContentControls/Window.h"
#include "Datas/ControlStyle.h"
#include "Datas/Coordinate.h"
#include	"RenderEngine.h"
#include "Datas/VisualCollection.h"
#include <glfw3.h>
Application Application::app;

Application::Application() : mouseDirectOverElement(nullptr), focusElement(nullptr), renderEngine(new RenderEngine())
{
}

Application::~Application()
{
	delete renderEngine;
}

bool Application::Init()
{
	if (!renderEngine->InitGUIEnvironment()) {
		return false;
	}
	return false;
}

void Application::Start()
{
	renderEngine->Start();
}


void Application::OnMouseMove(UIElement* win,double x,double y)
{
	MouseMoveEvent e(x, y);
	MousePositionHandle(e, win, 0);
}

void Application::OnMouseClick(int button, int buttonStatus, int mods)
{
	MouseButtonHandle(button, buttonStatus, mods);
}

void Application::OnWindowLeave(UIElement* win)
{
	while (!mouseOverElements.empty()) 
	{
		RaiseMouseLeaveEvent(*(mouseOverElements.back()));
		mouseOverElements.pop_back();
	}
}

void Application::OnKeyInput(int key, int scancode, int action, int mods)
{
	if (focusElement == nullptr)
		return;
	RaiseKeyInputEvent(*focusElement, key, action, mods);
}

void Application::OnTextInput(unsigned int code)
{
	if (focusElement == nullptr)
		return;
	RaiseTextInputEvent(*focusElement,code);
}


void Application::MousePositionHandle(MouseMoveEvent& e, UIElement*& element, size_t mouseOverElemntIndex)
{
	Point pt(element->vData.AreaSize().X(), element->vData.AreaSize().Y());
	Point::TranslatTo(pt, element->vData.AreaSize().ModelMatrix());
	Size size(pt.X(),pt.Y(), element->vData.AreaSize().Z(), element->vData.AreaSize().Width(), element->vData.AreaSize().Height());
	
	//����ؼ����ɼ��ͷ���
	/*if (element) {
		return;
	}*/
	//Ҫ������������������Ҫ�����ӻ���Ū��
	//����ָ�������ϲ�����ڵ㿪ʼ�����´��ݣ�ͬ���Ľڵ㰴��zֵ��С˳��zֵԽ��Խ�Ƚ��յ��¼�
	// ������������������ָ��ؼ��ģ��ÿؼ��ᱻ���뵽һ��˫������std::deque�У����μ��룬ÿһ���ؼ���������������һ��ؼ���˭��ָ���
	// ��һ������ƶ��¼���ָ��Ŀؼ����������еĿؼ����бȽϣ��жϸò��µ�ָ��ؼ��Ƿ���ԭ��һ��
	// ��һ��ʱ������������Ĳ���
	// ����һ��ʱ����˫������Ĵ˴��Լ��������пؼ��������ܱ����ָ����ô��Щ�ؼ���Ҫ�����¼�MouseLeave
	// �����ָ��ؼ��Ĵ�����ֹ���ò�ؼ�����һ���Ƿ��ܹ�������¼�Ϊ���������ܹ�����ʱ���������´���
	// ���޷�����ʱ���˴������¼���ֹλ�ã�Ҳ�����ֱ��ָ��ؼ�
	
	//�˴��жϱ���ô��ؼ��Ѿ�������˫��������ʾ�Ĳ��
	//�ò��Լ�������εĿؼ�������˫������Ԫ�رȽ�
	//����������Ӹò�ε����ָ��տؼ�
	if (mouseOverElemntIndex == mouseOverElements.size()) {
		if (size.PointIn(e.X(), e.Y())) {
			element->isMouseOver = true;
			element->isMouseDirectOver = true;
			mouseOverElements.emplace_back(element);
			++mouseOverElemntIndex;
			//��������
			for (auto& child : *(element->visualTree)) {
				MousePositionHandle(e, (UIElement*&)child, mouseOverElemntIndex);
				if (e.handled){
					element->isMouseDirectOver = false;
					break;
				}
			}
			//����MouseEnter�¼�
			RaiseMouseEnterEvent(*element);
			e.handled = true;
			if(element->isMouseDirectOver)
				mouseDirectOverElement = element;
			return;
		}
		//���ھ�ֱ��return;
		return;
	}
	
	//���±�ʾ�����ָ��Ŀؼ��Ĳ������˫������Ĳ����
	//��Ҫ��˫����������Ӧ�Ĳ�ν��бȽ�
	
	//�ô��ж����ò�εĿؼ���������¼�Ŀؼ�
	if (mouseOverElements[mouseOverElemntIndex] == element) {
		//������ڿؼ���
		if (size.PointIn(e.X(), e.Y())) {
			element->isMouseDirectOver = true;
			//����premouseOver�¼�
			RaisePreMouseOverEvent(*element,e.X(), e.Y());
			++mouseOverElemntIndex;
			//���´���
			for (auto& child : *(element->visualTree)) {
				MousePositionHandle(e, (UIElement*&)child, mouseOverElemntIndex);
				if (e.handled) {
					element->isMouseDirectOver = false;
					break;
				}
			}
			
			//����mouseOver�¼�
			RaiseMouseOverEvent(*element,e.X(), e.Y());
			e.handled = true;
			if(element->isMouseDirectOver)
				mouseDirectOverElement = element;
			return;
		}
		//��겻�ٿؼ���
		//���ò㼫����������пؼ��ļ�¼ȫ��ɾ��
		//��������ؼ���mouseover״̬
		ReMoveMouseOverElements(mouseOverElemntIndex);
		//int index = mouseOverElements.size() - 1;
		//while (index >= mouseOverElemntIndex) {
		//	//�ÿؼ�����λ�ü������Ŀؼ���������MouseLeave�¼�
		//	mouseOverElements[index]->isMouseOver = false;
		//	mouseOverElements[index]->isMouseDirectOver = false;
		//	RaiseMouseLeaveEvent(*(mouseOverElements[index]));
		//	mouseOverElements.pop_back();
		//	--index;
		//	
		//}
		//�������ͽ����˿ؼ�����β��
		return;
	}

	//�������ͬ
	if (size.PointIn(e.X(), e.Y())) {
		element->isMouseOver = true;
		element->isMouseDirectOver = true;
		ReMoveMouseOverElements(mouseOverElemntIndex);

		//int index = mouseOverElements.size() - 1;
		//while (index >= mouseOverElemntIndex) {
		//	mouseOverElements[index]->isMouseOver = false;
		//	mouseOverElements[index]->isMouseDirectOver = false;
		//	//����mouseleave
		//	RaiseMouseLeaveEvent(*(mouseOverElements[index]));
		//	mouseOverElements.pop_back();
		//	--index;
		//}
		mouseOverElements.emplace_back(element);
		//��ʱҲ�ǿؼ�����β��
		++mouseOverElemntIndex;
		//���´���
		for (auto& child : *(element->visualTree)) {
			MousePositionHandle(e, (UIElement*&)child, mouseOverElemntIndex);
			if (e.handled){
				element->isMouseDirectOver = false;
				break;
			}
		}
		//����mouseenter�¼�
		RaiseMouseEnterEvent(*element);
		e.handled = true;
		if (element->isMouseDirectOver) 
			mouseDirectOverElement = element;
		return;
	}
	//���û����
	return;
}

void Application::MouseButtonHandle(int button, int buttonStatus, int mods)
{

	int btn = 0;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		button = MOUSE_LEFT_BUTTON;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		button = MOUSE_RIGHT_BUTTON;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		button = MOUSE_MIDDLE_BUTTON;
		break;
	default:
		button = 0;
		break;
	}
	if (buttonStatus == GLFW_PRESS) {
		RaisePreMouseDownEvent(button, 0);
		RaiseMouseDownEvent(button, 0);
	}
	else {
		RaisePreMouseUpEvent(button, 0);
		RaiseMouseUpEvent(button, 0);
	}
	//���ý���
	if (focusElement != mouseDirectOverElement) {
		if (focusElement != nullptr) {
			focusElement->focus = false;
			focusElement->OnLostFocus();
		}
		if (mouseDirectOverElement->focusable) {
			mouseDirectOverElement->focus = true;
			focusElement = mouseDirectOverElement;
			mouseDirectOverElement->OnFocus();
		}
		
	}

}

inline void Application::RaisePreMouseOverEvent(UIElement& element,const int& x, const int& y)
{
	PreMouseOverEvent e(x, y);
	element.OnPreMouseOver(e);
}

inline void Application::RaiseMouseOverEvent(UIElement& element,const int& x,const int& y)
{
	MouseOverEvent e(x, y);
	element.OnMouseOver(e);
}

inline void Application::RaiseMouseEnterEvent(UIElement& element)
{
	MouseEnterEvent e;
	element.OnMouseEnter(e);
}

inline void Application::RaiseMouseLeaveEvent(UIElement& element)
{
	MouseLeaveEvent e;
	element.OnMouseLeave(e);
}



void Application::RaisePreMouseDownEvent(int button, int mods)
{
	PreMouseButtonDownEvent e(button, false);
	for (auto& child : mouseOverElements) {
		child->OnPreMouseDown(e);
	}
}

void Application::RaisePreMouseUpEvent(int button, int mods)
{
	PreMouseButtonUpEvent e(button);
	for (auto& child : mouseOverElements) {
		child->OnPreMouseUp(e);
	}
}

void Application::RaiseMouseDownEvent(int button, int mods)
{
	
	switch (button)
	{
	case MOUSE_LEFT_BUTTON:
	{
		MouseLeftButtonDownEvent e(false);
		mouseDirectOverElement->OnMouseLeftButtonDown(e);
	}
	break;
	case MOUSE_RIGHT_BUTTON:
	{
		MouseRightButtonDownEvent e(false);
		mouseDirectOverElement->OnMouseRightButtonDown(e);
	}
	break;
	case MOUSE_MIDDLE_BUTTON:
	{
		MouseMiddleButtonDownEvent e(false);
		mouseDirectOverElement->OnMouseMiddleButtonDown(e);
	}
	break;
	default:
		break;
	}
}

void Application::RaiseMouseUpEvent(int button, int mods)
{
	switch (button)
	{
	case MOUSE_LEFT_BUTTON:
	{
		MouseLeftButtonUpEvent e;
		mouseDirectOverElement->OnMouseLeftButtonUp(e);
	}
	break;
	case MOUSE_RIGHT_BUTTON:
	{
		MouseRightButtonUpEvent e;
		mouseDirectOverElement->OnMouseRightButtonUp(e);
	}
	break;
	case MOUSE_MIDDLE_BUTTON:
	{
		MouseMiddleButtonUpEvent e;
		mouseDirectOverElement->OnMouseMiddleButtonUp(e);
	}
	break;
	default:
		break;
	}
}

inline void Application::RaiseKeyInputEvent(UIElement& element, int key, int action, int mods)
{
	
	if (action == GLFW_PRESS) {
		KeyPressedEvent e(key, false);
		element.OnKeyPress(e);
	}
	else {
		KeyUpEvent e(key);
		element.OnKeyUp(e);
	}
}

inline void Application::RaiseTextInputEvent(UIElement& element, unsigned int code)
{
	TextInputEvent e(code);
	element.OnTextInput(e);
}

void Application::ReMoveMouseOverElements(unsigned int from)
{
	while (mouseOverElements.size() > from) {
		mouseOverElements.back()->isMouseOver = false;
		mouseOverElements.back()->isMouseDirectOver = false;
		//����mouseleave
		RaiseMouseLeaveEvent(*(mouseOverElements.back()));
		mouseOverElements.pop_back();
	}
}


void LeaveWindowCallBack(GLFWwindow* winHD, int entered)
{
	if (entered == GLFW_FALSE) {
		Window* window = (Window*)glfwGetWindowUserPointer(winHD);
		Application::app.OnWindowLeave(window);
	}
}

void KeyInputCallBack(GLFWwindow* winHD, int key, int scancode, int action, int mods)
{
	Application::app.OnKeyInput(key, scancode, action, mods);
}

void TextInputCallBack(GLFWwindow* winHD, unsigned int code)
{
	Application::app.OnTextInput(code);
}

void MouseMoveCallBack(GLFWwindow* winHD, double xpos, double ypos)
{
	Window* window = (Window*)glfwGetWindowUserPointer(winHD);
	Application::app.OnMouseMove((UIElement*)window, xpos, ypos);
}

void MouseButtonCallBack(GLFWwindow* winHD, int button, int status, int mods)
{
	Application::app.OnMouseClick(button, status, mods);
}
