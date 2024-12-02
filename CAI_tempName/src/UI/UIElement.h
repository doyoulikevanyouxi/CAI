#pragma once
#include "Object.h"
#include "Visual.h"
#include "Events/Events.h"
#include "Animation/StoryBord.h"
class PaintDevice;
class ControlTemplate;
class Size;

/// <summary>
/// 继承至Visual，在其基础上添加了事件的响应和动画
/// 事件部分不完善仍需开发
/// </summary>
class UIElement : public Object, public Visual
{
	friend class RenderEngine;
	friend class Application;
public:
	UIElement(UIElement* parent = nullptr) noexcept;
	UIElement(const UIElement& other) noexcept;
	virtual ~UIElement() noexcept;

public:
	//重载了Visual的渲染：需要添加动画效果
	virtual void Render() override;
	void SetParent(UIElement* parent);
	//开始动画
	void BeginAnimation();
/// <summary>
/// 以下为事件响应函数，Pre-Event事件是从上往下传递的事件
/// </summary>
protected:
	virtual void OnFocus();
	virtual void OnLostFocus();
	virtual void OnPreMouseDown(PreMouseButtonDownEvent& e);
	virtual void OnMouseLeftButtonDown(MouseLeftButtonDownEvent& e);
	virtual void OnMouseRightButtonDown(MouseRightButtonDownEvent& e);
	virtual void OnMouseMiddleButtonDown(MouseMiddleButtonDownEvent& e);
	virtual void OnPreMouseUp(PreMouseButtonUpEvent& e);
	virtual void OnMouseLeftButtonUp(MouseLeftButtonUpEvent& e);
	virtual void OnMouseRightButtonUp(MouseRightButtonUpEvent& e);
	virtual void OnMouseMiddleButtonUp(MouseMiddleButtonUpEvent& e);
	virtual void OnMouseLeave(MouseLeaveEvent& e);
	virtual void OnMouseEnter(MouseEnterEvent& e);
	virtual void OnPreMouseOver(PreMouseOverEvent& e);
	virtual void OnMouseOver(MouseOverEvent& e);
	virtual void OnKeyPress(KeyPressedEvent& e);
	virtual void OnKeyUp(KeyUpEvent& e);
	virtual void OnTextInput(InputEvent& e);
	virtual void OnEvent(EventAbstract& e);
	virtual void RaiseEvent(EventAbstract& e);
protected:
	ControlTemplate* style;
	UIElement* parent;
public:
	//故事板，包括了该控件的所有，同一时段下所有动画
	StoryBord storybord;
};

