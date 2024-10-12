#pragma once
#include "ContentControl.h"
/// <summary>
/// 定义了一行的属性
/// </summary>
class RowDefinition : public ContentControl
{
public:
	RowDefinition() noexcept { name = "RowDefinition"; }
	//RowDefinition(const RowDefinition& other) {};
	~RowDefinition() noexcept {}
};

