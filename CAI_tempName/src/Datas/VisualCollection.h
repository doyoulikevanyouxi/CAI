#pragma once
#include "Collection.h"
#include "UI/Visual.h"
class VisualCollection : public Collection<Visual*>
{
public:
	void SortByZindex();
};

