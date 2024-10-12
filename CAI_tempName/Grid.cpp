#include "Grid.h"

Grid::Grid() noexcept
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
