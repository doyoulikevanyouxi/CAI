#pragma once
#include "UI/UIElement.h"
/// <summary>
/// ����һ������Ŀؼ����ÿؼ���������Ļ���Ԫ����ӵ�ָ���Ŀؼ���
/// </summary>
class Decoration : public UIElement
{
public:
	Decoration()= delete;
	Decoration(UIElement* attachto) noexcept;
	virtual ~Decoration() noexcept;
};

