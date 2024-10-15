#pragma once
#include"Object.h"
#include "Collection.h"
#include "VisualData.h"
/// <summary>
/// ����ͼ�εĻ��Ʊ���,����������Ļ������Ժ�ֱ���Ӻ��ӵļ���
/// </summary>
class ControlStyle : public Object
{
public:
	ControlStyle() noexcept;
	ControlStyle(const ControlStyle& other) {
		visualTree = other.visualTree;
		vData = other.vData;
	}
	virtual ~ControlStyle() noexcept;
public:
	void addChildToVisual(UIElement& child) { visualTree.addChild(&child); }
	VisualData& styleData() noexcept { return vData; }
public:
	ControlStyle& operator=(const ControlStyle& other) {
		if (&other == this)
			return *this;
		visualTree = other.visualTree;
		vData = other.vData;
		return *this;
	}
public:
	UIElementCollection visualTree;
private:
	friend class UIElement;
	friend class Panel;
	friend class PaintDevice;
	VisualData vData;
};