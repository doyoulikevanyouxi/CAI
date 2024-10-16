#pragma once
#include"Element.h"
#include"Draw.h"
#include "Property.hpp"
class PaintDevice;
class ControlTemplate;
class Size;
extern float zmax;
/// <summary>
/// ���п��ӻ�Ԫ�صĻ��࣬�����˿��ӻ�Ԫ�ر��������λ�ã���С����ɫ
/// λ�úʹ�С�����˾������㣬Ŀǰ��������cpu�ϼ��㣬����������Ǩ����
/// GPU���м���
/// </summary>
class UIElement : public Element
{
public:
	UIElement(UIElement* parent = nullptr) noexcept;
	UIElement(const UIElement& other) noexcept;
	virtual ~UIElement() noexcept;
public:
	/// <summary>
	/// ͼ����Ⱦ
	/// </summary>
	virtual void render() noexcept;
	void setControlStyeData() noexcept;
public:
	//����һ�����Լ̳й�ϵ
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
	//Ϊ�Լ������ؼ���С��λ��
	void beginInit(const Size& size) noexcept;
	Size& getSize();
protected:
	virtual Size measure(const Size& size) noexcept;
	virtual void aeasure(const Size& size) noexcept;
public:
	/// <summary>
	/// ע����ǣ��������������Ǹ������л��Ƶ����벼�ֵĿؼ�ʹ�õ�
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

