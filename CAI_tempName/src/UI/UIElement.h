#pragma once
#include "Object.h"
#include "Visual.h"
#include "Events/Events.h"
#include "Animation/StoryBord.h"
class PaintDevice;
class ControlTemplate;
class Size;

/// <summary>
/// ���п��ӻ�Ԫ�صĻ��࣬�����˿��ӻ�Ԫ�ر��������λ�ã���С����ɫ
/// λ�úʹ�С�����˾������㣬Ŀǰ��������cpu�ϼ��㣬����������Ǩ����
/// GPU���м���
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
	//����һ�����Լ̳й�ϵ
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

