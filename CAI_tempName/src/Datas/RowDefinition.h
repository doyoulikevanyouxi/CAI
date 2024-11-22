#pragma once
#include "Object.h"
/// <summary>
/// 定义了一行的属性
/// </summary>
class RowDefinition : public Object
{
public:
	RowDefinition(float height = 0,bool validHeight = false) noexcept :y(0), height(height),validHeight(validHeight){ name = CAISTR(RowDefinition);}
	~RowDefinition() noexcept = default;
	void SetHeight(float& value) { height = value; validHeight = true; }
public:
	float y;
	float height;
	bool validHeight;
};

/// <summary>
/// 定义了一列的属性
/// </summary>
class ColumDefinition : public Object {
public:
	ColumDefinition(float width=0,bool validWidth =false) noexcept:x(0),width(width),validWidth(validWidth){ name = CAISTR(ColumDefinition); }
	~ColumDefinition() noexcept = default;
	void SetWidth(float& value) { width = value; validWidth = true; }
public:
	float x;
	float width;
	bool validWidth;
};