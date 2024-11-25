#pragma once
#include "Events/Events.h"
struct GLFWwindow;
class RenderEngine;
class UIElement;
/// <summary>
/// �����������
/// ���������ƶ�
/// </summary>
class Application
{
public:
	static Application app;
private:
	Application();
	~Application();
public:
	bool Init();
	void Start();
/// <summary>
/// ��ԭʼ���¼����ݽ��д���
/// </summary>
public:
	void OnMouseMove(UIElement* win,double x,double y);
	void OnMouseClick(int button, int buttonStatus, int mods);
	void OnWindowLeave(UIElement* win);
	void OnKeyInput(int key, int scancode, int action, int mods);
	void OnTextInput(unsigned int code);
private:
	//��������ƶ��¼�
	void MousePositionHandle(MouseMoveEvent& e, UIElement*& element,size_t mousOverElemntIndex);
	inline void MouseButtonHandle(int button,int buttonStatus,int mods);
	inline void RaisePreMouseOverEvent(UIElement& element,const int& x ,const int& y);
	inline void RaiseMouseOverEvent(UIElement& element,const int& x,const int& y);
	inline void RaiseMouseEnterEvent(UIElement& element);
	inline void RaiseMouseLeaveEvent(UIElement& element);
	inline void RaisePreMouseDownEvent(int button,int mods);
	inline void RaisePreMouseUpEvent(int button, int mods);
	inline void RaiseMouseDownEvent(int button,int mods);
	inline void RaiseMouseUpEvent(int button,int mods);
	inline void RaiseKeyInputEvent(UIElement& element, int key, int action, int mods);
	inline void RaiseTextInputEvent(UIElement& element, unsigned int code);
private:
	void ReMoveMouseOverElements(unsigned int from);
private:
	//���ֱ��ָ��Ŀؼ�
	UIElement* mouseDirectOverElement;
	//����ؼ�
	UIElement* focusElement;
	std::deque<UIElement*> mouseOverElements;
public:
	RenderEngine* renderEngine;
};

void LeaveWindowCallBack(GLFWwindow* winHD, int entered);
void KeyInputCallBack(GLFWwindow* winHD, int key, int scancode, int action, int mods);
void TextInputCallBack(GLFWwindow* winHD, unsigned int code);
void MouseMoveCallBack(GLFWwindow* winHD, double xpos, double ypos);
void MouseButtonCallBack(GLFWwindow* winHD, int button , int status, int mods);