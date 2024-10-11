#pragma once
#include"EControl.h"
class ContentControl : public Control
{
public:
	ContentControl()	noexcept;
	virtual ~ContentControl() noexcept;
public:
	void setContent(Object& elem);
public:
	DependencyProperty<Object*> content{ "Content" };
};

