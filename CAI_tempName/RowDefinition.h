#pragma once
#include "ContentControl.h"
/// <summary>
/// ������һ�е�����
/// </summary>
class RowDefinition : public ContentControl
{
public:
	RowDefinition() noexcept { name = "RowDefinition"; }
	//RowDefinition(const RowDefinition& other) {};
	~RowDefinition() noexcept {}
};

