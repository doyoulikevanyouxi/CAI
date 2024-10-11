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
	/// ͼ����Ⱦ
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
	//Ϊ�Լ������ؼ���С��λ��
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
	/// �ؼ���ʵ����Ⱦ����
	/// </summary>
	float actualWidth;
	/// <summary>
	/// �ؼ�ʵ����Ⱦ�߶�
	/// </summary>
	float actualHeight;
	UIElement* parent;
	//������openGL���õ���Դ
protected:
	PaintDevice* pDevice;
};

