#pragma once
#include "UIElement.h"
#include "Border.h"
class Control : public UIElement
{
public:
	Control() noexcept;
	virtual ~Control() noexcept;
public:
	//Border* border;
public:
	void show();
};

