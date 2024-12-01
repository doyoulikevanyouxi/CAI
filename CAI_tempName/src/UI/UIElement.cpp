#include "caipch.h"
#include "UIElement.h"
#include "Datas/ControlStyle.h"
#include"Datas/Collection.h"
#include"Datas/coordinate.h"
#include<glad/glad.h>
#include"PaintDeivces/PaintDevice.h"
#include"Shader.h"
#include"RenderEngine.h"
#include "Events/Events.h"
UIElement::UIElement(UIElement* parent) noexcept :Visual(parent), style(new ControlTemplate()), parent(parent)
{

}

UIElement::UIElement(const UIElement& other) noexcept :UIElement(nullptr)
{
	*style = *other.style;
}

UIElement::~UIElement() noexcept
{
	delete style;
}



void UIElement::Render()
{
	if (!storybord.Empty()) {
		if (storybord.IsBegin()) {
			storybord.Excut();
		}
	}
	Visual::Render();
}

void UIElement::SetParent(UIElement* parent)
{
	this->parent = parent;
}

void UIElement::BeginAnimation()
{
	if (storybord.Empty())
		return;
	storybord.BeginAnimation();
}

void UIElement::OnPreMouseDown(PreMouseButtonDownEvent& e)
{
}

void UIElement::OnMouseLeftButtonDown(MouseLeftButtonDownEvent& e)
{
}

void UIElement::OnMouseRightButtonDown(MouseRightButtonDownEvent& e)
{
}

void UIElement::OnMouseMiddleButtonDown(MouseMiddleButtonDownEvent& e)
{
}

void UIElement::OnPreMouseUp(PreMouseButtonUpEvent& e)
{
}

void UIElement::OnMouseLeftButtonUp(MouseLeftButtonUpEvent& e)
{
}

void UIElement::OnMouseRightButtonUp(MouseRightButtonUpEvent& e)
{
}

void UIElement::OnMouseMiddleButtonUp(MouseMiddleButtonUpEvent& e)
{
}
void UIElement::OnMouseLeave(MouseLeaveEvent& e)
{
}

void UIElement::OnMouseEnter(MouseEnterEvent& e)
{
}

void UIElement::OnPreMouseOver(PreMouseOverEvent& e)
{
}

void UIElement::OnMouseOver(MouseOverEvent& e)
{
}

void UIElement::OnTextInput(InputEvent& e)
{
}

void UIElement::OnEvent(EventAbstract& e)
{
	//Ìí¼Ó¹ýÂË£¬¹ýÂËµô±ÜÃâ¼ÌÐø´«µÝ
	/*if (eventDispatcher.filter(e))
		return;*/
		/*switch (e.GetEventPreType())
		{
		case	 EventType::InputEvent:
			OnTextInput((InputEvent&)e);
			break;
		default:
			break;
		}
		switch (e.GetEventType())
		{
		default:
			break;
		}
		if (e.handled)
			return;
		switch (e.sType)
		{
		case EventSpreadType::Tunnel:
			for (auto& child : style->visualTree) {
				child->OnEvent(e);
				if (e.handled)
					return;
			}
			break;
		case EventSpreadType::Bubble:
			parent->OnEvent(e);
			break;
		case EventSpreadType::Direct:
			break;
		default:
			break;
		}*/
}

void UIElement::RaiseEvent(EventAbstract& e)
{
	switch (e.sType)
	{
	case EventSpreadType::Tunnel:
		OnEvent(e);
		break;
	case EventSpreadType::Bubble:
		OnEvent(e);
		break;
	case EventSpreadType::Direct:
		if (e.source == nullptr || e.target == nullptr)
			break;
		((UIElement*)(e.target))->OnEvent(e);
		break;
	default:
		break;
	}
}
