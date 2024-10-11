#include "UIElement.h"
#include "ControlStyle.h"
#include "VisualTree.h"
#include"UIElementCollection.h"
#include"coordinate.h"
#include<glad/glad.h>
#include"PaintDevice.h"
UIElement::UIElement(UIElement* parent) noexcept :style(new ControlStyle()), parent(parent), pDevice(new PaintDevice())
{
	width = 0.f;
	height = 0.f;
	maxWidth = -1.f;
	maxHeight = -1.f;
	/*actualWidth = size->Width();
	actualHeight = size->Height();*/
	pDevice->setWindow(nullptr);
	pDevice->setPen(Brush(0xff000000));
	style->brush = Brush(0xff000000);
	style->size.setCoordinat(0, 0);
}

UIElement::~UIElement() noexcept
{
	delete style;
	delete pDevice;
}

void UIElement::render() noexcept
{
	//pDevice->DrawRect(Point(0, 0), 0.5, 0.5);
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
	style->size.Height() = value;
}

void UIElement::setWidth(float value)
{
	width.set(value);
	style->size.Width() = value;
}

void UIElement::setBackground(const Draw::Brush& color)
{
	background.set(color);
	style->brush = color;
}

void UIElement::measure(const Size& size) noexcept
{
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
	style->init();
	//style->vData.test();
	for (auto& child : style->visualTree) {
		child->measure(style->size);
	}
}

