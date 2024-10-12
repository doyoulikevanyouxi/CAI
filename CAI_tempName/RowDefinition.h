#pragma once
#include "ContentControl.h"
/// <summary>
/// 定义了一行的属性
/// </summary>
class RowDefinition : public ContentControl
{
public:
	RowDefinition() noexcept { name = "RowDefinition";}
	~RowDefinition() noexcept {}
private:
	void setWidth(float value) noexcept override {}
};

/// <summary>
/// 定义了一列的属性
/// </summary>
class ColumDefinition : public ContentControl {
public:
	ColumDefinition() noexcept { name = "ColumnDefinition"; }
	~ColumDefinition() noexcept {}
private:
	void setHeight(float value) noexcept override {}
};