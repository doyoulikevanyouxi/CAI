#pragma once
#include "ContentControl.h"
/// <summary>
/// ������һ�е�����
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
/// ������һ�е�����
/// </summary>
class ColumDefinition : public ContentControl {
public:
	ColumDefinition() noexcept { name = "ColumnDefinition"; }
	~ColumDefinition() noexcept {}
private:
	void setHeight(float value) noexcept override {}
};