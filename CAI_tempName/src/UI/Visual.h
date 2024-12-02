#pragma once
#include "Datas/Collection.h"
#include "Datas/VisualData.h"
#include "Datas/Property.hpp"
#include "Draw.h"
class PaintDevice;
class VisualCollection;
//这是记录最大的z值，因为需要知道z值分布
extern float zmax;

/// <summary>
/// 可视化控件的基类，所有控件的最总绘制都在此处
/// 这是原型，仍需要优化
/// </summary>
class Visual 
{
	friend class Application;
public:
	Visual(Visual* parent);
	Visual(const Visual& other);
	~Visual();
public:
	//用于获取绘制元素的绘制设备句柄
	virtual bool Init();
	//调用绘制句柄绘制
	virtual void Render();
	//设置可视元素的父元素
	void SetVisualParent(Visual* parent);
	//添加可视元素子元素
	void AddVisualChild(Visual* child);
	//获取可视元素父元素
	inline Visual* GetVisualParent() { return parent; }
	//获取可视化树---可视化子元素几何
	inline VisualCollection* GetVisulTree() { return visualTree; }
public:
	void operator=(const Visual& other);
public:
	//以下为获取或设置元素外观：大小，边框，颜色等
	virtual void SetHeight(float value);
	virtual void SetWidth(float value);
	virtual void SetZindex(float value);
	virtual void SetBorderSize(float value);
	void SetWidthAndHeight(float width, float height);
	void SetMinHeight(float value);
	void SetMinWidth(float value);
	void SetMaxHeight(float value);
	void SetMaxWidth(float value);
	void SetBackground(const Draw::Brush& color);
	void SetBackground(const uint32_t color);
	void SetBorderBrush(const Draw::Brush& color);
	void SetVisible(const bool visible);
	void SetRadius(const float& value);
	inline float GetActualWidth() const noexcept { return actualWidth; }
	inline float GetActualHeight() const noexcept { return actualHeight; }
public:
	//为自己测量控件大小和位置
	void CheckSize(const Size& size) noexcept;
	Size& GetSize();
	bool* GetVisible() { return &(vData.Visible()); }
protected:
	//测量自身的元素位置以及大小，并初始化绘制数据
	virtual Size Measure(const Size& size) noexcept;
	virtual void Aeasure(const Size& size) noexcept;
private:
	//设置实际的高度
	inline void SetActualHeight(float value);
	//设置实际的宽度
	inline void SetActualWidth(float value);
/// <summary>
/// 可是元素的固有属性
/// </summary>
public:
	DependencyProperty<float> width{ "Width" };
	DependencyProperty<float> height{ "Height" };
	DependencyProperty<float> minWidth{ "MinWidth" };
	DependencyProperty<float> minHeight{ "MinHeight" };
	DependencyProperty<float> maxWidth{ "MaxWidth" };
	DependencyProperty<float> maxHeight{ "MaxHeight" };
	DependencyProperty<float> zIndex{ "Z-index" };
	DependencyProperty<Draw::Brush> background{ "Background" };
	DependencyProperty<float> borderSize{ "Border-Size" };
	DependencyProperty<float> shadow{ "Border-Size" };
	DependencyProperty<float> fontSize{ "FontSize" };
	DependencyProperty<bool> visible{ "Visible" };
	DependencyProperty<float> radius{ "Radius" };

public:
	//是否是焦点
	bool focusable = true;
	bool focus = false;
	//鼠标在元素内是否移动
	bool isMouseOver = false;
	//鼠标的直接指向是否是该元素
	bool isMouseDirectOver = false;
	//鼠标是否进入
	bool isMouseEnter = false;
protected:
	float actualWidth = 0.f;
	float actualHeight = 0.f;
	bool validWidth = false;
	bool validHeight = false;
protected:
	//可视化父元素
	Visual* parent;
	//绘制数据
	VisualData vData;
	//可视化树
	VisualCollection* visualTree;
protected:
	//绘制设备
	PaintDevice* pDevice;
};
//VisualCollection
