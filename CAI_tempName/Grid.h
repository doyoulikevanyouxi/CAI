#pragma once
#include "Panel.h"
#include "RowDefinition.h"
using RowDefinitionCollection = Collection<RowDefinition>;

class Grid : public Panel
{
public:
	Grid() noexcept;
	virtual ~Grid() noexcept;
public:
	void addRowDefinition(const RowDefinition& rowDefine);
public:
	RowDefinitionCollection rowDeinitions;
public:
	DependencyProperty<int> colums{ "Colums" };
	DependencyProperty<int> rows{ "Rows" };

};

