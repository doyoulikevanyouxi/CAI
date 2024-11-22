#pragma once
#include "../EControl.h"
#include "Datas/Collection.h"
#include"Mathmatics/Math.hpp"
/// <summary>
/// Panel控件允许为所以容纳的控件进行排版和大小设定
/// 不继承至Control下是因为布局容器本身是没有太多的渲染数据
/// 布局控件的实质是设置一个变换矩阵，使得该控件下的子元素根据变换矩阵进行变换
/// 关于整体的缩放矩阵暂时不会添加进来。而要计算的是子元素的大小及位置
/// </summary>
class Panel : public Control
{
public:
	Panel() noexcept;
	virtual ~Panel();
public:
	virtual void AddChild(UIElement* child);

protected:
	UIElementCollection childs;
protected:
	Math::TransMatrix transMatrix;
	/// <summary>
	/// x增量
	/// </summary>
	float xIncrement;
	/// <summary>
	/// y增量
	/// </summary>
	float yIncrement;
};

