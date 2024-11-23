#pragma once
#include"Object.h"
#include "Datas/Collection.h"
#include "VisualData.h"
//#include "UI/UIElement.h"
/// <summary>
/// ����ͼ�εĻ��Ʊ���,����������Ļ������Ժ�ֱ���Ӻ��ӵļ���
/// </summary>
class ControlTemplate : public Object
{
	friend class UIElement;
	friend class Panel;
	friend class PaintDevice;
	friend class Application;
public:
	ControlTemplate() noexcept {}
	ControlTemplate(const ControlTemplate& other) {
		visualTree = other.visualTree;
		vData = other.vData;
	}
	virtual ~ControlTemplate() noexcept {}
public:
	void addChildToVisual(UIElement& child) { visualTree.AddChild(&child); }
	VisualData& styleData() noexcept { return vData; }
public:
	ControlTemplate& operator=(const ControlTemplate& other) {
		if (&other == this)
			return *this;
		visualTree = other.visualTree;
		vData = other.vData;
		return *this;
	}
public:
	UIElementCollection visualTree;
private:
	VisualData vData;
};