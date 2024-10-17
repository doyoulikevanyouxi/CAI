#pragma once
#include "Decoration.h"
#include "Draw.h"
/// <summary>
/// Border控件即显示所附加控件的边框
/// </summary>
class Border : public Decoration
{
	using Decoration::Decoration;
//public:
//	Border(UIElement* attachedto) noexcept:Decoration(attachedto) {}
//	~Border()noexcept {}
private:
	friend class Control;
	float size;
	Draw::Color color;
};

