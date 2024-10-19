#pragma once
#include "UI/UIElement.h"
enum RelativeLocation
{
	Center,
	Left,
	Top,
	Right,
	Bottom
};
class Control : public UIElement
{
public:
	Control() noexcept;
	virtual ~Control() noexcept;
public:
	void setMargin(float left,float top = 0.f,float right=0.f,float bottom=0.f) noexcept;
	void setHorizontalAlignment(RelativeLocation value);
	void setVerticalAlignment(RelativeLocation value);
protected:
	virtual Size measure(const Size& size) noexcept override;
public:
	DependencyProperty<float> marginL{ "Margin-Left" };
	DependencyProperty<float> marginR{ "Margin-Right" };
	DependencyProperty<float> marginT{ "Margin-Top" };
	DependencyProperty<float> marginB{ "Margin-Bottom" };
	//œ‡∂‘Œª÷√
	DependencyProperty<RelativeLocation> horizontAlalignment{ "HorizontalAlignment" };
	DependencyProperty<RelativeLocation> verticalAlignment{ "VerticalAlignment" };
public:
	void show();
};

