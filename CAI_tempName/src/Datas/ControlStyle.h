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
		
	}
	virtual ~ControlTemplate() noexcept {}
public:
	ControlTemplate& operator=(const ControlTemplate& other) {
		if (&other == this)
			return *this;
		return *this;
	}
public:

};