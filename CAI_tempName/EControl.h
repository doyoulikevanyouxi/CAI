#pragma once
#include "UIElement.h"
class Control : public UIElement
{
public:
	Control() noexcept;
	virtual ~Control() noexcept;
public:
	void show();
};

