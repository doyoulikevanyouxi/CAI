#include "UIElement.h"
#include "ControlStyle.h"
#include "VisualTree.h"
#include"Collection.h"
#include"coordinate.h"
#include<glad/glad.h>
#include"PaintDevice.h"
UIElement::UIElement(UIElement* parent) noexcept :style(new ControlStyle()), parent(parent), pDevice(new PaintDevice())
{
	actualWidth = 0.f;
	actualHeight = 0.f;
	pDevice->setWindow(nullptr);
	pDevice->setPen(Brush(0xff000000));
	style->brush = Brush(0xff000000);
	style->size.setCoordinat(0, 0);
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
	//setActualHeight();
	
}

void UIElement::setWidth(float value)
{
	width.set(value);
	//setActualWidth();
	
}

void UIElement::setMinHeight(float value)
{
	minHeight.set(value);
	//setActualHeight();
}

void UIElement::setMinWidth(float value)
{
	minWidth.set(value);
	//setActualWidth();
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
	style->brush = color;
}

void UIElement::beginInit(const Size& size) noexcept
{
	aeasure(measure(size));
	style->init();
}

Size UIElement::measure(const Size& size) noexcept
{
	setActualHeight();
	setActualWidth();
	if (actualHeight > size.Height())
		actualHeight = size.Height();
	if (actualWidth >= size.Width())
		actualWidth = size.Width();
	style->size.Width() = actualWidth;
	style->size.Height() = actualHeight;
	//接着将根据给定的父变换矩阵来设置控件自身的变换矩阵
	Math::SquareMatrix<4> tMatrix = {
									1,0,0,size.X(),
									0,1,0,size.Y(),
									0,0,1,0,
									0,0,0,1
	};
	style->size.DPH() = size.DPH();
	style->size.DPW() = size.DPW();
	style->size.TransMatrix() = size.TransMatrix() * tMatrix;
	return style->size;
}

void UIElement::aeasure(const Size& size) noexcept
{
	for (auto& child : style->visualTree) {
		child->beginInit(size);
	}
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
				style->size.Width() = actualWidth;
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
				style->size.Height() = actualHeight;
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
	return style->size;
}


