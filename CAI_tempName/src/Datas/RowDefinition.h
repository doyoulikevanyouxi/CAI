#pragma once
#include "Controls/ContentControl.h"
/// <summary>
/// ������һ�е�����
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
/// ������һ�е�����
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