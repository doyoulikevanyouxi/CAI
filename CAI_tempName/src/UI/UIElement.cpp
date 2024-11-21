#include "caipch.h"
#include "UIElement.h"
#include "Datas/ControlStyle.h"
#include"Datas/Collection.h"
#include"Datas/coordinate.h"
#include<glad/glad.h>
#include"PaintDevice.h"
#include"Shader.h"
#include"RenderEngine.h"
float zmax = 1;
UIElement::UIElement(UIElement* parent) noexcept :style(new ControlTemplate()), parent(parent), pDevice(new PaintDevice())
{
	actualWidth = 0.f;
	actualHeight = 0.f;
	pDevice->SetWindow(nullptr);
	pDevice->SetPen(Brush(0xff000000));
	style->vData.AreaBrush() = Brush(0x00000000);
	style->vData.AreaSize().setX(0);
	style->vData.AreaSize().setY(0);
}

UIElement::UIElement(const UIElement& other) noexcept :UIElement(nullptr)
{
	width = other.width.get();
	height = other.height.get();
	maxWidth = other.maxWidth.get();
	maxHeight = other.maxHeight.get();
	minWidth = other.minWidth.get();
	minHeight = other.minHeight.get();
	actualWidth = other.actualWidth;
	actualHeight = other.actualHeight;
	background = other.background.get();
	pDevice->SetWindow(nullptr);
	pDevice->SetPen(other.pDevice->GetPen());
	*style = *other.style;
}

UIElement::~UIElement() noexcept
{
	delete style;
	delete pDevice;
}

void UIElement::Render() noexcept
{
	pDevice->Draw(style);	
	//裁剪测试，由于float精度问题，可能存在裁剪过后存在间隙
	for (auto& element : style->visualTree) {
		element->Render();
	}
}

void UIElement::SetControlStyeData() noexcept
{

}

void UIElement::SetParent(UIElement* parent)
{
	this->parent = parent;
}

void UIElement::SetHeight(float value)
{
	height.set(value);
	SetActualHeight(value);
	validHeight = true;
}

void UIElement::SetWidth(float value)
{
	width.set(value);
	SetActualWidth(value);
	validWidth = true;
}

void UIElement::SetZindex(float value)
{
	zIndex.set(value);
}

void UIElement::SetBorderSize(float value)
{
	borderSize.set(value);
}

void UIElement::SetWidthAndHeight(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

void UIElement::SetMinHeight(float value)
{
	minHeight.set(value);
	if (actualHeight < value)
		actualHeight = value;
	validHeight = true;
}

void UIElement::SetMinWidth(float value)
{
	minWidth.set(value);
	if (actualWidth < value) {
		actualWidth = value;
	}
	validWidth = true;
}

void UIElement::SetMaxHeight(float value)
{
	maxHeight.set(value);
	if (actualHeight > value)
		actualHeight = value;
	validHeight = true;
}

void UIElement::SetMaxWidth(float value)
{
	maxWidth.set(value);
	if (actualWidth > value)
		actualWidth = value;
	validWidth = true;
}

void UIElement::SetBackground(const Draw::Brush& color)
{
	background.set(color);
	style->vData.AreaBrush() = color;
}

void UIElement::SetBackground(const uint32_t color)
{
	background.set(Draw::Brush(color));
	style->vData.AreaBrush() = Draw::Brush(color);
}

void UIElement::SetBorderBrush(const Draw::Brush& color)
{
	*(style->vData.borderBrush) = color;
}

void UIElement::BeginInit(const Size& size) noexcept
{
	Aeasure(Measure(size));
	style->vData.InitData();
}

Size UIElement::Measure(const Size& size) noexcept
{
	style->vData.AreaSize().SetGlobalWidth(size.GlobalWidth());
	style->vData.AreaSize().SetGlobalHeight(size.GlobalHeight());
	Point tmp(size.X(), size.Y());
	tmp.Y() += size.Height();
	Point::TranslatTo(tmp, size.TransMatrix());
	Point::SetToLeftBottom(tmp, size.GlobalHeight());
	//设置裁减区域
	style->vData.clipSize->setX(tmp.X());
	style->vData.clipSize->setY(tmp.Y());
	style->vData.clipSize->SetWidth(size.Width());
	style->vData.clipSize->SetHeight(size.Height());
	//未设置宽度值时，采用传递过来的大小
	if (width.IsInvalid()) {
		SetActualWidth(size.Width());
	}
	if (height.IsInvalid()) {
		SetActualHeight(size.Height());
	}
	style->vData.AreaSize().SetWidth(actualWidth);
	style->vData.AreaSize().SetHeight(actualHeight);
	//接着将根据给定的父变换矩阵来设置控件自身的变换矩阵
	Math::SquareMatrix<4> tMatrix = {
									1,0,0,0,
									0,1,0,0,
									0,0,1,0,
									size.X(),size.Y(),0,1
	};
	//如果z值未设置，那么将继承上个z值并+1
	if (zIndex.IsInvalid())
		style->vData.AreaSize().setZ(size.Z() + 1);
	style->vData.AreaSize().TransMatrix() = size.TransMatrix() * tMatrix;
	if (zmax < style->vData.AreaSize().Z())
		zmax = style->vData.AreaSize().Z();
	//如果有边框，就将边框加入
	if (!borderSize.IsInvalid())
		style->vData.SetBorderSize(borderSize.get());
	//初始化控件顶点数据
	style->vData.InitData();
	return style->vData.ContentSize();
}

void UIElement::Aeasure(const Size& size) noexcept
{
	for (auto& child : style->visualTree) {
		child->BeginInit(size);
	}
}

void UIElement::OnMouseOver(CAITF::MouseMoveEvent& e)
{
	e.handled = false;
}

void UIElement::OnInput(CAITF::InputEvent& e)
{
}

void UIElement::OnEvent(CAITF::EventAbstract& e)
{
	//添加过滤，过滤掉避免继续传递
	if (eventDispatcher.filter(e))
		return;
	switch (e.GetEventPreType())
	{
	case	CAITF::EventType::InputEvent:
		OnInput((CAITF::InputEvent&)e);
		break;
	default:
		break;
	}
	switch (e.GetEventType())
	{
	case	CAITF::EventSubType::MouseMoveEvent: {
		OnMouseOver((CAITF::MouseMoveEvent&)e);
	}
		break;
	default:
		break;
	}
	if (e.handled)
		return;
	switch (e.sType)
	{
	case CAITF::EventSpreadType::Tunnel:
		for (auto& child : style->visualTree) {
			child->OnEvent(e);
			if (e.handled)
				return;
		}
		break;
	case CAITF::EventSpreadType::Bubble:
		parent->OnEvent(e);
		break;
	case CAITF::EventSpreadType::Direct:
		break;
	default:
		break;
	}
	
	
}

void UIElement::RaiseEvent(CAITF::EventAbstract& e)
{
	switch (e.sType)
	{
	case CAITF::EventSpreadType::Tunnel:
		OnEvent(e);
		break;
	case CAITF::EventSpreadType::Bubble:
		OnEvent(e);
		break;
	case CAITF::EventSpreadType::Direct:
		if (e.source == nullptr || e.target == nullptr)
			break;
		((UIElement*)(e.target))->OnEvent(e);
		break;
	default:
		break;
	}
}

inline void UIElement::SetActualHeight(float value)
{
	actualHeight = value;
	if (!minHeight.IsInvalid()) {
		if (value < minHeight.get()) {
			actualHeight = minHeight.get();
		}
	}
	if (!maxHeight.IsInvalid()) {
		if (value > maxHeight.get()) {
			actualHeight = maxHeight.get();
		}
	}

}

inline void UIElement::SetActualWidth(float value)
{
	actualWidth = value;
	if (!minWidth.IsInvalid()) {
		if (value < minWidth.get()) {
			actualWidth = minWidth.get();
		}
	}
	if (!maxWidth.IsInvalid()) {
		if (value > maxWidth.get()) {
			actualWidth = maxWidth.get();
		}
	}
}

Size& UIElement::GetSize()
{
	return style->vData.AreaSize();
}


