#include "TedPanel.h"
#include "ControlStyle.h"
#include"Coordinate.h"
TedPanel::TedPanel() noexcept
{
	name = "TedPanel";
	width = 800;
	height = 600;
}

TedPanel::~TedPanel() noexcept
{
}

void TedPanel::measure(const Size& size) noexcept
{
	//x = size.point().X();
	//y = size.point().Y();
	//this->size->setPoint({ x,y });
	//if (width.get() > size.Width())
	//	width = size.Width();
	//if (height.get() > size.Height())
	//	height = size.Height();
	//if (Width() < MinWidth() && MinWidth() >= 0)
	//	width = MinWidth();
	//if (Width() > MaxWidth() && MaxWidth() >= 0)
	//	width = MaxWidth();
	//if (Height() < MinHeight() && MinHeight() >= 0)
	//	height = MinHeight();
	//if (Height() > MaxHeight() && MaxHeight() >= 0)
	//	height = MaxHeight();
	//this->size->Width() = Width();
	//this->size->Height() = Height();
	//Size tmp(*this->size);
	//for (auto& child : *style->vTree->visualChilds) {
	//	child->measure(tmp);
	//	tmp.point().X() = x + child->Width();
	//	tmp.point().Y() = y + child->Height();
	//	tmp.Width() = tmp.Width() - child->Width();
	//}
}

void TedPanel::AddChild(UIElement* child)
{
	childs.addChild(child);
	//style->vTree->visualChilds->addChild(child);
}

void TedPanel::init(Size& size)
{
	measure(size);
}
