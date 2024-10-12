#pragma once
#include"Object.h"
#include "VisualTree.h"
#include "Collection.h"
#include "Draw.h"
#include "Coordinate.h"
/// <summary>
/// 决定图形的绘制表现,包括了自身的绘制属性和直接子孩子的集合
/// </summary>
class ControlStyle : public Object
{
public:
	ControlStyle() noexcept;
	ControlStyle(const ControlStyle& other) {
		visualTree = other.visualTree;
		size = other.size;
		brush = other.brush;
	}
	virtual ~ControlStyle() noexcept;
public:
	void addChildToVisual(UIElement& child) { visualTree.addChild(&child); }
	void setCoor(float x,float y) {}
	const VisualData& getData() const { return vData; }
	VisualData& getData()  { return vData; }
	void init() { vData.setData(size, brush); }
public:
	ControlStyle& operator=(const ControlStyle& other) {
		visualTree = other.visualTree;
		size = other.size;
		brush = other.brush;
		return *this;
	}
public:
	UIElementCollection visualTree;
private:
	friend class UIElement;
	friend class Panel;
	VisualData vData;
	Size size;
	Draw::Brush brush;
};