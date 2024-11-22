#pragma once
#include "Events/Events.h"
#include <stack>
class UIElement;
/// <summary>
/// 程序控制中心
/// 会监听鼠标移动
/// </summary>
class ApplicationControl
{
public:
	static ApplicationControl app;
public:
	void OnMouseMove(MouseMoveEvent& e, UIElement* win);
private:
	void MouseMouseHandle(MouseMoveEvent& e,UIElement*& element,size_t mousOverElemntIndex);
	ApplicationControl();
private:
	UIElement* currentElement;
	//用于鼠标进入的控件，每进入一个控件就往里压入一个
	//判断进入标准是：父控件肯定进入，主要是子控件，多个子控件可能重合在一起，这时候需要从z值最大的一个控件开始传递消息
	//如果z值最大的进入了，那么其他的就没有进入
	//当部分重合时，存在情况就是如果先进入最大的z值控件，那么就不存在
	std::deque<UIElement*> eles;
};

