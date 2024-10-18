#include "UIElement.h"
#include "ControlStyle.h"
#include"Collection.h"
#include"coordinate.h"
#include<glad/glad.h>
#include"PaintDevice.h"

#include"Shader.h"
#include"RenderEngine.h"
float zmax = 1;
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
	//裁剪测试，由于float精度问题，可能存在裁剪过后存在间隙
	glEnable(GL_SCISSOR_TEST);
	Size sz = style->vData.ContentSize().transto();
	glScissor(sz.X(), sz.Y(), sz.Width(), sz.Height());
	for (auto& element : style->visualTree) {
		element->render();
	}
	glDisable(GL_SCISSOR_TEST);
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

void UIElement::setZindex(float value)
{
	zIndex.set(value);
	style->vData.AreaSize().setZ(value);
}

void UIElement::setBorderSize(float value)
{
	borderSize.set(value);
	style->vData.setBorderSize(value);
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
}

void UIElement::setMaxWidth(float value)
{
	maxWidth.set(value);
}

void UIElement::setBackground(const Draw::Brush& color)
{
	background.set(color);
	style->vData.AreaBrush() = color;
}

void UIElement::setBorderBrush(const Draw::Brush& color)
{
	*(style->vData.borderBrush) = color;
}

void UIElement::beginInit(const Size& size) noexcept
{
	aeasure(measure(size));
	style->vData.initData();
}

Size UIElement::measure(const Size& size) noexcept
{
	setActualHeight();
	setActualWidth();
	if (actualHeight > size.Height() && height.isInvalid())
		actualHeight = size.Height();
	if (actualWidth >= size.Width() && width.isInvalid())
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
	if (zIndex.isInvalid())
		style->vData.AreaSize().setZ(size.Z() + 1);
	style->vData.AreaSize().TransMatrix() = size.TransMatrix() * tMatrix;
	if (zmax < style->vData.AreaSize().Z())
		zmax = style->vData.AreaSize().Z();
	
	return style->vData.ContentSize();
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
			height = actualHeight = parent->actualHeight;
		}
		else {
			if (!minHeight.isInvalid()) {
				actualHeight = minHeight.get();
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


