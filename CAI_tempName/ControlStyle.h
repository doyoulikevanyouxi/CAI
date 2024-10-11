#pragma once
#include"Object.h"
#include "VisualTree.h"
#include "UIElementCollection.h"
#include "Draw.h"
#include "Coordinate.h"
/// <summary>
/// ����ͼ�εĻ��Ʊ���,����������Ļ������Ժ�ֱ���Ӻ��ӵļ���
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