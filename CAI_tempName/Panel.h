#pragma once
#include "UIElement.h"
#include "UIElementCollection.h"
/// <summary>
/// Panel控件允许为所以容纳的控件进行排版和大小设定，前提是子控件没有强行设置自己的位置和属性
/// 不继承至Control下是因为布局容器本身是没有太多的渲染数据
/// </summary>
class Panel : public UIElement
{
public:
	Panel() noexcept;
	virtual ~Panel();
protected:
	UIElementCollection childs;
};

