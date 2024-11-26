#pragma once
#include "Datas/Collection.h"
#include "Datas/VisualData.h"
#include "Datas/Property.hpp"
#include "Draw.h"
class PaintDevice;
class VisualCollection;
extern float zmax;
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
	virtual void Render();
	void SetVisualParent(Visual* parent);
	void AddVisualChild(Visual* child);
	inline Visual* GetVisualParent() { return parent; }
	inline VisualCollection* GetVisulTree() { return visualTree; }
	inline Size& GetGlobalAreaSize() const { return vData.GlobalAreaSize(); }
public:
	void operator=(const Visual& other);
public:
	bool* GetVisible() { return &(vData.visibale); }

	virtual void SetHeight(float value);
	virtual void SetWidth(float value);
	virtual void SetZindex(float value);
	void SetBorderSize(float value);
	void SetWidthAndHeight(float width, float height);
	void SetMinHeight(float value);
	void SetMinWidth(float value);
	void SetMaxHeight(float value);
	void SetMaxWidth(float value);
	void SetBackground(const Draw::Brush& color);
	void SetBackground(const uint32_t color);
	void SetBorderBrush(const Draw::Brush& color);
	void SetVisible(const bool visible);
	inline float GetActualWidth() const noexcept { return actualWidth; }
	inline float GetActualHeight() const noexcept { return actualHeight; }
public:
	//为自己测量控件大小和位置
	void CheckSize(const Size& size) noexcept;
	Size& GetSize();
protected:
	virtual Size Measure(const Size& size) noexcept;
	virtual void Aeasure(const Size& size) noexcept;
private:
	inline void SetActualHeight(float value);
	inline void SetActualWidth(float value);
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

public:
	bool focus = false;
	bool isMouseOver = false;
	bool isMouseDirectOver = false;
	bool isMouseEnter = false;
protected:
	float actualWidth = 0.f;
	float actualHeight = 0.f;
	bool validWidth = false;
	bool validHeight = false;
protected:
	Visual* parent;
	VisualData vData;
	VisualCollection* visualTree;
protected:
	PaintDevice* pDevice;
	
};
//VisualCollection
