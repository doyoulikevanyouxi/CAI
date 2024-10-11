#pragma once
#include "Panel.h"
class Grid : public Panel
{
public:
	Grid() noexcept;
	virtual ~Grid() noexcept;
public:
	//RowDefinitionCollection rowDeinition;
public:
	DependencyProperty<int> colum{ "Colum" };
	DependencyProperty<int> row{ "Colum" };

};

