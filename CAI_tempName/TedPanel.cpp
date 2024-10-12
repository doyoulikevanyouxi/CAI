#include "TedPanel.h"
#include "ControlStyle.h"
#include"Coordinate.h"
TedPanel::TedPanel() noexcept
{
	name = "TedPanel";
}

TedPanel::~TedPanel() noexcept
{
}

void TedPanel::aeasure(const Size& size) noexcept
{
	Size tmp(size);
	float preChildWidth = 0.f;
	for (auto& child : style->visualTree) {
		transMatrix[0][3] = xIncrement;
		tmp.TransMatrix() = size.TransMatrix()* transMatrix;
		//tmp.setX(size.X() + xIncrement);
		child->beginInit(tmp);
		xIncrement += child->getActualWidth()+10;
	}
}


