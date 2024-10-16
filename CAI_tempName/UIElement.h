#pragma once
#include"Element.h"
#include"Draw.h"
#include "Property.hpp"
class PaintDevice;
class ControlTemplate;
class Size;
extern float zmax;
/// <summary>
/// 所有可视化元素的基类，定义了可视化元素必须的量：位置，大小，颜色
/// 位置和大小采用了矩阵运算，目前矩阵是在cpu上计算，后续将矩阵迁移至
/// GPU进行计算
/// </summary>
class UIElement : public Element
{
public:
	UIElement(UIElement* parent = nullptr) noexcept;
	UIElement(const UIElement& other) noexcept;
	virtual ~UIElement() noexcept;
public:
	/// <summary>
	/// 图形渲染
	/// </summary>
	virtual void render() noexcept;
	void setControlStyeData() noexcept;
public:
	//会有一个属性继承关系
	void setParent(UIElement* parent);
	virtual void setHeight(float value);
	virtual void setWidth(float value);
	virtual void setZindex(float value);
	void setWidthAndHeight(float width, float height);
	void setMinHeight(float value);
	void setMinWidth(float value);
	void setMaxHeight(float value);
	void setMaxWidth(float value);
	void setBackground(const Draw::Brush& color);
	inline float getActualWidth() const noexcept { return actualWidth; }
	inline float getActualHeight() const noexcept { return actualHeight; }
	ControlTemplate& getControlTemplate() { return *style; }
	//void setProperty();
public:
	//为自己测量控件大小和位置
	void beginInit(const Size& size) noexcept;
	Size& getSize();
protected:
	virtual Size measure(const Size& size) noexcept;
	virtual void aeasure(const Size& size) noexcept;
public:
	/// <summary>
	/// 注意的是，以下两个函数是给不进行绘制但参与布局的控件使用的
	/// </summary>
	/// <param name="value"></param>
	void setActualWidth(float value);
	void setActualHeight(float value);
private:
	void setActualWidth();
	void setActualHeight();

public:
	DependencyProperty<float> width{ "Width" };
	DependencyProperty<float> height{ "Height" };
	DependencyProperty<float> minWidth{ "MinWidth" };
	DependencyProperty<float> minHeight{ "MinHeight" };
	DependencyProperty<float> maxWidth{ "MaxWidth" };
	DependencyProperty<float> maxHeight{ "MaxHeight" };
	DependencyProperty<float> zIndex{ "Z-index" };
	DependencyProperty<Draw::Brush> background{ "Background" };
protected:
	ControlTemplate* style;
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

