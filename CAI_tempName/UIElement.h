#pragma once
#include"Element.h"
#include"Draw.h"
#include "Property.hpp"
class PaintDevice;
class ControlStyle;
class Size;
class UIElement : public Element
{
public:
	UIElement(UIElement* parent=nullptr) noexcept;
	virtual ~UIElement() noexcept;
public:
	/// <summary>
	/// 图形渲染
	/// </summary>
	virtual void render() noexcept;
	void setControlStyeData() noexcept;
public:
	void setParent(UIElement* parent);
	void setHeight(float value);
	void setWidth(float value);
	void setBackground(const Draw::Brush& color);
	inline float getActualWidth() const noexcept{ return actualWidth; }
	inline float getActualHeight() const noexcept{ return actualHeight; }
	//void setProperty();
public:
	//为自己测量控件大小和位置
	virtual void measure(const Size& size) noexcept;
public:
	DependencyProperty<float> width{"Width"};
	DependencyProperty<float> height{"Height"};
	DependencyProperty<float> minWidth{ "MinWidth" };
	DependencyProperty<float> minHeight{ "MinHeight" };
	DependencyProperty<float> maxWidth{ "MaxWidth" };
	DependencyProperty<float> maxHeight{ "MaxHeight" };
	DependencyProperty<Draw::Brush> background{ "Background" };
protected:
	ControlStyle* style;
private:
	/// <summary>
	/// 控件的实际渲染长度
	/// </summary>
	float actualWidth;
	/// <summary>
	/// 控件实际渲染高度
	/// </summary>
	float actualHeight;
	UIElement* parent;
	//以下是openGL所用到资源
protected:
	PaintDevice* pDevice;
};

