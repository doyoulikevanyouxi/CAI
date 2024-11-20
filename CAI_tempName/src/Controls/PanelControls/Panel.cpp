#include "caipch.h"
#include "Panel.h"
#include "Datas/ControlStyle.h"
Panel::Panel() noexcept:xIncrement(0.f),yIncrement(0.f)
{
	transMatrix = {
					1,0,0,xIncrement,
					0,1,0,yIncrement,
					0,0,1,0,
					0,0,0,1
				};
}

Panel::~Panel()
{

}

void Panel::addChild(UIElement& child)
{
	childs.addChild(&child);
	//加入到可视化树中
	style->visualTree.addChild(&child);
	child.SetParent(this);
}

