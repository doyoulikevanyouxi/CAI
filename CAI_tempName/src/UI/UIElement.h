#pragma once
#include "Object.h"
#include "Visual.h"
#include "Events/Events.h"
#include "Animation/StoryBord.h"
class PaintDevice;
class ControlTemplate;
class Size;

/// <summary>
/// 所有可视化元素的基类，定义了可视化元素必须的量：位置，大小，颜色
/// 位置和大小采用了矩阵运算，目前矩阵是在cpu上计算，后续将矩阵迁移至
/// GPU进行计算
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
	//会有一个属性继承关系
	virtual void Render() override;
	void SetParent(UIElement* parent);
	void BeginAnimation();
protected:
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

	virtual void OnTextInput(InputEvent& e);
	virtual void OnEvent(EventAbstract& e);
	virtual void RaiseEvent(EventAbstract& e);
protected:
	ControlTemplate* style;
	UIElement* parent;
public:
	StoryBord storybord;
};

