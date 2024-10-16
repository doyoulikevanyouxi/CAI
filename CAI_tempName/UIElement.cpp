#include "UIElement.h"
#include "ControlStyle.h"

#include"Collection.h"
#include"coordinate.h"
#include<glad/glad.h>
#include"PaintDevice.h"
UIElement::UIElement(UIElement* parent) noexcept :style(new ControlTemplate()), parent(parent), pDevice(new PaintDevice())
{
	actualWidth = 0.f;
	actualHeight = 0.f;
	pDevice->setWindow(nullptr);
	pDevice->setPen(Brush(0xff000000));
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
	pDevice->setWindow(nullptr);
	pDevice->setPen(other.pDevice->getPen());
	*style = *other.style;
}

UIElement::~UIElement() noexcept
{
	delete style;
	delete pDevice;
}

void UIElement::render() noexcept
{
	pDevice->Draw(style);
	for (auto& element : style->visualTree) {
		element->render();
	}
}

void UIElement::setControlStyeData() noexcept
{

}

void UIElement::setParent(UIElement* parent)
{
	this->parent = parent;
}

void UIElement::setHeight(float value)
{
	height.set(value);
}

void UIElement::setWidth(float value)
{
	width.set(value);
}

void UIElement::setWidthAndHeight(float width, float height)
{
	this->width.set(width);
	this->height.set(height);
}

void UIElement::setMinHeight(float value)
{
	minHeight.set(value);
}

void UIElement::setMinWidth(float value)
{
	minWidth.set(value);
}

void UIElement::setMaxHeight(float value)
{
	maxHeight.set(value);
	//setActualHeight();
}

void UIElement::setMaxWidth(float value)
{
	maxWidth.set(value);
	//setActualWidth();
}

void UIElement::setBackground(const Draw::Brush& color)
{
	background.set(color);
	style->vData.AreaBrush() = color;
}

void UIElement::beginInit(const Size& size) noexcept
{
	aeasure(measure(size));
}

Size UIElement::measure(const Size& size) noexcept
{
	setActualHeight();
	setActualWidth();
	if (actualHeight > size.Height())
		actualHeight = size.Height();
	if (actualWidth >= size.Width())
		actualWidth = size.Width();
	style->vData.AreaSize().setWidth(actualWidth);
	style->vData.AreaSize().setHeight(actualHeight);
	//接着将根据给定的父变换矩阵来设置控件自身的变换矩阵
	Math::SquareMatrix<4> tMatrix = {
									1,0,0,0,
									0,1,0,0,
									0,0,1,0,
									size.X(),size.Y(),0,1
	};
	style->vData.AreaSize().TransMatrix() = size.TransMatrix() * tMatrix;
	return style->vData.AreaSize();
}

void UIElement::aeasure(const Size& size) noexcept
{
	for (auto& child : style->visualTree) {
		child->beginInit(size);
	}
}

void UIElement::setActualWidth(float value)
{
	actualWidth = value;
}

void UIElement::setActualHeight(float value)
{
	actualHeight = value;
}

void UIElement::setActualWidth()
{
	if (width.isInvalid()) {
		if (parent != nullptr) {
			width = actualWidth = parent->actualWidth;
		}
		else {
			if (!minWidth.isInvalid()) {
				actualWidth = minWidth.get();
				style->vData.AreaSize().setWidth(actualWidth);
				return;
			}
			else {
				actualWidth = 0.f;
			}

		}
	}
	else {
		actualWidth = width.get();
	}
	if (actualWidth < minWidth.get() && !minWidth.isInvalid())
		actualWidth = minWidth.get();
	else if (actualWidth > maxWidth.get() && !maxWidth.isInvalid())
		actualWidth = maxWidth.get();
}

void UIElement::setActualHeight()
{
	if (height.isInvalid()) {
		if (parent != nullptr) {
			height=actualHeight = parent->actualHeight;
		}
		else {
			if (!minHeight.isInvalid()) {
				actualHeight = minHeight.get();
				style->vData.AreaSize().setHeight(actualHeight);

				return;
			}
			else {
				actualHeight = 0.f;
			}
				
		}
	}
	else {
		actualHeight = height.get();
	}
	if (actualHeight < minHeight.get() && !minHeight.isInvalid())
		actualHeight = minHeight.get();
	else if (actualHeight > maxHeight.get() && !maxHeight.isInvalid())
		actualHeight = maxHeight.get();
}

Size& UIElement::getSize()
{
	return style->vData.AreaSize();
}


