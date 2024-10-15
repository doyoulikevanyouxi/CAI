#include "Grid.h"
#include "ControlStyle.h"
#include "Coordinate.h"
Grid::Grid() noexcept :rFixedNum(0),cFixedNum(0)
{
	name = "Grid";
}

Grid::~Grid() noexcept
{

}

void Grid::addRowDefinition(const RowDefinition& rowDefine)
{
	rowDeinitions.addChild(rowDefine);
}

void Grid::addColumDefinition(const ColumDefinition& columDefine)
{
	columDeinitions.addChild(columDefine);
}

void Grid::setRow(UIElement* target, int row)
{
	this->row.get().insert({ target,row });
}

void Grid::setColum(UIElement* target, int colum)
{
	this->colum.get().insert({ target,colum });
}

void Grid::setRC(UIElement* target, int row, int colum)
{
	this->row.get().insert({ target,row });
	this->colum.get().insert({ target,colum });
}

void Grid::aeasure(const Size& size) noexcept
{
	float he = actualHeight / rowDeinitions.Size();
	for (auto& r : rowDeinitions) {

		r.setHeight(he);
		r.getSize().setY(yIncrement);
		yIncrement += he;
	}
	float wd = actualWidth / columDeinitions.Size();
	for (auto& c : columDeinitions) {
		c.setWidth(wd);
		c.getSize().setX(xIncrement);
		xIncrement += wd;
	}

	Size tmp(size);
	float preChildWidth = 0.f;
	auto Ro = row.get();
	auto Co = colum.get();
	for (auto& child : style->visualTree) {
		int r = Ro[child];
		int c = Co[child];
		RowDefinition& Rod = rowDeinitions[r];
		ColumDefinition& Cod = columDeinitions[c];
		const Size& szR = Rod.getSize();
		const Size& szC = Cod.getSize();
		tmp.setX(szC.X());
		tmp.setY(szR.Y());
		tmp.setWidth(Cod.width.get());
		tmp.setHeight(Rod.height.get());
		child->beginInit(tmp);
	}
}
