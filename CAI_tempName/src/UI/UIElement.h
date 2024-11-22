#pragma once
#include"Element.h"
#include"Draw.h"
#include "Datas/Property.hpp"
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
	friend class RenderEngine;
	friend class ApplicationControl;
public:
	UIElement(UIElement* parent = nullptr) noexcept;
	UIElement(const UIElement& other) noexcept;
	virtual ~UIElement() noexcept;
public:
	/// <summary>
	/// ͼ����Ⱦ
	/// </summary>
	virtual void Render() noexcept;
	void SetControlStyeData() noexcept;
public:
	//����һ�����Լ̳й�ϵ
	void SetParent(UIElement* parent);
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
	inline float GetActualWidth() const noexcept { return actualWidth; }
	inline float GetActualHeight() const noexcept { return actualHeight; }
	ControlTemplate& GetControlTemplate() { return *style; }
	//void setProperty();
public:
	//Ϊ�Լ������ؼ���С��λ��
	void BeginInit(const Size& size) noexcept;
	Size& GetSize();
protected:
	virtual Size Measure(const Size& size) noexcept;
	virtual void Aeasure(const Size& size) noexcept;
protected:
	/*virtual void OnResize() override;
	virtual void OnRender() override;
	virtual void OnMouseOver() override;
	virtual void OnMouseLeftButtonPress() override;
	virtual void OnMouseLeftButtonUp() override;*/
	// ͨ�� Element �̳�
	virtual void OnMouseLeave(MouseLeaveEvent& e) override;
	virtual void OnMouseEnter(MouseEnterEvent& e) override;
	virtual void OnPreMouseOver(PreMouseOverEvent& e) override;
	virtual void OnMouseOver(MouseOverEvent& e) override;
	virtual void OnInput(InputEvent& e) override;
	virtual void OnEvent(EventAbstract& e) override;
	virtual void RaiseEvent(EventAbstract& e) override;
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
public:
	bool focus = false;
	bool needReRender = false;
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

	bool validWidth = false;
	bool validHeight = false;
	//������openGL���õ���Դ
protected:
	PaintDevice* pDevice;


};

