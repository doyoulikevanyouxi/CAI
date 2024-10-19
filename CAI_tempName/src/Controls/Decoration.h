#pragma once
#include "UI/UIElement.h"
/// <summary>
/// 这是一个特殊的控件，该控件允许将额外的绘制元素添加到指定的控件上
/// </summary>
class Decoration : public UIElement
{
public:
	Decoration()= delete;
	Decoration(UIElement* attachto) noexcept;
	virtual ~Decoration() noexcept;
};

