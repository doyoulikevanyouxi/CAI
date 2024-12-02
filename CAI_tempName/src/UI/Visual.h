#pragma once
#include "Datas/Collection.h"
#include "Datas/VisualData.h"
#include "Datas/Property.hpp"
#include "Draw.h"
class PaintDevice;
class VisualCollection;
//���Ǽ�¼����zֵ����Ϊ��Ҫ֪��zֵ�ֲ�
extern float zmax;

/// <summary>
/// ���ӻ��ؼ��Ļ��࣬���пؼ������ܻ��ƶ��ڴ˴�
/// ����ԭ�ͣ�����Ҫ�Ż�
/// </summary>
class Visual 
{
	friend class Application;
public:
	Visual(Visual* parent);
	Visual(const Visual& other);
	~Visual();
public:
	//���ڻ�ȡ����Ԫ�صĻ����豸���
	virtual bool Init();
	//���û��ƾ������
	virtual void Render();
	//���ÿ���Ԫ�صĸ�Ԫ��
	void SetVisualParent(Visual* parent);
	//��ӿ���Ԫ����Ԫ��
	void AddVisualChild(Visual* child);
	//��ȡ����Ԫ�ظ�Ԫ��
	inline Visual* GetVisualParent() { return parent; }
	//��ȡ���ӻ���---���ӻ���Ԫ�ؼ���
	inline VisualCollection* GetVisulTree() { return visualTree; }
public:
	void operator=(const Visual& other);
public:
	//����Ϊ��ȡ������Ԫ����ۣ���С���߿���ɫ��
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
	//Ϊ�Լ������ؼ���С��λ��
	void CheckSize(const Size& size) noexcept;
	Size& GetSize();
	bool* GetVisible() { return &(vData.Visible()); }
protected:
	//���������Ԫ��λ���Լ���С������ʼ����������
	virtual Size Measure(const Size& size) noexcept;
	virtual void Aeasure(const Size& size) noexcept;
private:
	//����ʵ�ʵĸ߶�
	inline void SetActualHeight(float value);
	//����ʵ�ʵĿ��
	inline void SetActualWidth(float value);
/// <summary>
/// ����Ԫ�صĹ�������
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
	//�Ƿ��ǽ���
	bool focusable = true;
	bool focus = false;
	//�����Ԫ�����Ƿ��ƶ�
	bool isMouseOver = false;
	//����ֱ��ָ���Ƿ��Ǹ�Ԫ��
	bool isMouseDirectOver = false;
	//����Ƿ����
	bool isMouseEnter = false;
protected:
	float actualWidth = 0.f;
	float actualHeight = 0.f;
	bool validWidth = false;
	bool validHeight = false;
protected:
	//���ӻ���Ԫ��
	Visual* parent;
	//��������
	VisualData vData;
	//���ӻ���
	VisualCollection* visualTree;
protected:
	//�����豸
	PaintDevice* pDevice;
};
//VisualCollection
