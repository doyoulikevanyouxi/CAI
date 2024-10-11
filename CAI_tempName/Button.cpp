#include "Button.h"
#include"ControlStyle.h"
#include"PaintDevice.h"
Button::Button() noexcept 
{
	name = "button";
	setWidth(200);
	setHeight(300);
	setBackground(Brush(Draw::Color::RED));
}

Button::~Button()
{
}

