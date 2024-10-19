#pragma once
#include "Controls/ContentControl.h"
/// <summary>
/// 定义了一行的属性
/// </summary>
class RowDefinition : public ContentControl
{
public:
	RowDefinition() noexcept :y(0){ name = "RowDefinition";}
	~RowDefinition() noexcept {}
public:
	float y;
private:
	void setWidth(float value) noexcept override {}
};

/// <summary>
/// 定义了一列的属性
/// </summary>
class ColumDefinition : public ContentControl {
public:
	ColumDefinition() noexcept:x(0){ name = "ColumnDefinition"; }
	~ColumDefinition() noexcept {}
public:
	float x;
private:
	void setHeight(float value) noexcept override {}
};