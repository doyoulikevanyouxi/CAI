#pragma once
#include"Object.h"
#include "VisualTree.h"
#include "UIElementCollection.h"
#include "Draw.h"
#include "Coordinate.h"
/// <summary>
/// 决定图形的绘制表现,包括了自身的绘制属性和直接子孩子的集合
/// </summary>
class ControlStyle : public Object
{
public:
	ControlStyle() noexcept;
	virtual ~ControlStyle() noexcept;
public:
	void addChildToVisual(UIElement& child) { visualTree.addChild(&child); }
	void setCoor(float x,float y) {}
	const VisualData& getData() const { return vData; }
	VisualData& getData()  { return vData; }
	void init() { vData.setData(size, brush); }
private:
	friend class UIElement;
	VisualData vData;
	UIElementCollection visualTree;
	Size size;
	Draw::Brush brush;
};