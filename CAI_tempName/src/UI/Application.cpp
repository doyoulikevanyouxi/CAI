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
	
	//如果控件不可见就返回
	/*if (element) {
		return;
	}*/
	//要理解下面操作，首先需要将可视化树弄懂
	//鼠标的指向由最上层的树节点开始，向下传递，同级的节点按照z值大小顺序，z值越大，越先接收到事件
	// 鼠标所经过的属于鼠标指向控件的，该控件会被加入到一个双向链表std::deque中，依次加入，每一个控件代表者整个树的一层控件是谁被指向的
	// 下一次鼠标移动事件所指向的控件会与链表中的控件进行比较，判断该层新的指向控件是否与原本一致
	// 当一致时，不会做过多的操作
	// 当不一致时，该双向链表的此处以及其后的所有控件都不可能被鼠标指向，那么这些控件需要发出事件MouseLeave
	// 鼠标所指向控件的传播终止，该层控件的下一次是否能够处理该事件为条件，当能够处理时，继续向下传递
	// 当无法处理时，此处就是事件终止位置，也是鼠标直接指向控件
	
	//此处判断表面该处控件已经超出了双链表所表示的层次
	//该层以及后续层次的控件不再与双链表中元素比较
	//但会向其添加该层次的鼠标指向空控件
	if (mouseOverElemntIndex == mouseOverElements.size()) {
		if (size.PointIn(e.X(), e.Y())) {
			element->isMouseOver = true;
			element->isMouseDirectOver = true;
			mouseOverElements.emplace_back(element);
			++mouseOverElemntIndex;
			//继续向下
			for (auto& child : *(element->visualTree)) {
				MousePositionHandle(e, (UIElement*&)child, mouseOverElemntIndex);
				if (e.handled){
					element->isMouseDirectOver = false;
					break;
				}
			}
			//发出MouseEnter事件
			RaiseMouseEnterEvent(*element);
			e.handled = true;
			if(element->isMouseDirectOver)
				mouseDirectOverElement = element;
			return;
		}
		//不在就直接return;
		return;
	}
	
	//以下表示，鼠标指向的控件的层次仍再双向链表的层次中
	//需要与双向链表中相应的层次进行比较
	
	//该处判定：该层次的控件仍是所记录的控件
	if (mouseOverElements[mouseOverElemntIndex] == element) {
		//鼠标仍在控件内
		if (size.PointIn(e.X(), e.Y())) {
			element->isMouseDirectOver = true;
			//发出premouseOver事件
			RaisePreMouseOverEvent(*element,e.X(), e.Y());
			++mouseOverElemntIndex;
			//向下传递
			for (auto& child : *(element->visualTree)) {
				MousePositionHandle(e, (UIElement*&)child, mouseOverElemntIndex);
				if (e.handled) {
					element->isMouseDirectOver = false;
					break;
				}
			}
			
			//发出mouseOver事件
			RaiseMouseOverEvent(*element,e.X(), e.Y());
			e.handled = true;
			if(element->isMouseDirectOver)
				mouseDirectOverElement = element;
			return;
		}
		//鼠标不再控件内
		//将该层极其后序层的所有控件的记录全部删除
		//并设置其控件的mouseover状态
		ReMoveMouseOverElements(mouseOverElemntIndex);
		//int index = mouseOverElements.size() - 1;
		//while (index >= mouseOverElemntIndex) {
		//	//该控件链该位置极其后面的控件都将发出MouseLeave事件
		//	mouseOverElements[index]->isMouseOver = false;
		//	mouseOverElements[index]->isMouseDirectOver = false;
		//	RaiseMouseLeaveEvent(*(mouseOverElements[index]));
		//	mouseOverElements.pop_back();
		//	--index;
		//	
		//}
		//处理完后就进入了控件链的尾部
		return;
	}

	//如果不相同
	if (size.PointIn(e.X(), e.Y())) {
		element->isMouseOver = true;
		element->isMouseDirectOver = true;
		ReMoveMouseOverElements(mouseOverElemntIndex);

		//int index = mouseOverElements.size() - 1;
		//while (index >= mouseOverElemntIndex) {
		//	mouseOverElements[index]->isMouseOver = false;
		//	mouseOverElements[index]->isMouseDirectOver = false;
		//	//发出mouseleave
		//	RaiseMouseLeaveEvent(*(mouseOverElements[index]));
		//	mouseOverElements.pop_back();
		//	--index;
		//}
		mouseOverElements.emplace_back(element);
		//此时也是控件链的尾部
		++mouseOverElemntIndex;
		//向下传递
		for (auto& child : *(element->visualTree)) {
			MousePositionHandle(e, (UIElement*&)child, mouseOverElemntIndex);
			if (e.handled){
				element->isMouseDirectOver = false;
				break;
			}
		}
		//发出mouseenter事件
		RaiseMouseEnterEvent(*element);
		e.handled = true;
		if (element->isMouseDirectOver) 
			mouseDirectOverElement = element;
		return;
	}
	//如果没进入
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
	//设置焦点
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
		//发出mouseleave
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
