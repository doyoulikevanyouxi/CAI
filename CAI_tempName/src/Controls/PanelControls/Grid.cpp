#include "caipch.h"
#include "Grid.h"
#include "Datas/ControlStyle.h"
#include "Datas/Coordinate.h"
Grid::Grid() noexcept :rNoneFixedNum(0), cNoneFixedNum(0),totalFixedHeight(0.f),totalFixedWidth(0.f)
{
	name = CAISTR(Grid);
}

Grid::~Grid() noexcept
{

}

void Grid::addRowDefinition(const RowDefinition& rowDefine)
{
	rowDeinitions.addChild(rowDefine);
	if (!rowDefine.validHeight)
		++rNoneFixedNum;
	else
		totalFixedHeight += rowDefine.height;
}

void Grid::addColumDefinition(const ColumDefinition& columDefine)
{
	columDeinitions.addChild(columDefine);
	if (!columDefine.validWidth)
		++cNoneFixedNum;
	else
		totalFixedWidth += columDefine.width;
}

void Grid::setRow(UIElement* target, int row)
{
	if (childGridData.find(target) == childGridData.end()) {
		ControlGridData gData = {
			row,
			0,
			0,
			0
		};
		childGridData.insert({ target,gData });
	}
	else {
		childGridData[target].row = row;
	}
}

void Grid::setRowSpan(UIElement* target, int rowSpan)
{
	if (childGridData.find(target) == childGridData.end()) {
		ControlGridData gData = {
			0,
			rowSpan,
			0,
			0
		};
		childGridData.insert({ target,gData });
	}
	else {
		childGridData[target].rowSpan = rowSpan;
	}
}

void Grid::setColum(UIElement* target, int colum)
{
	if (childGridData.find(target) == childGridData.end()) {
		ControlGridData gData = {
			0,
			0,
			colum,
			0
		};
		childGridData.insert({ target,gData });
	}
	else {
		childGridData[target].colum = colum;
	}
}

void Grid::setColumSpan(UIElement* target, int columSpan)
{
	if (childGridData.find(target) == childGridData.end()) {
		ControlGridData gData = {
			0,
			0,
			0,
			columSpan
		};
		childGridData.insert({ target,gData });
	}
	else {
		childGridData[target].columSpan = columSpan;
	}
}

void Grid::setRC(UIElement* target, int row, int colum)
{
	if (childGridData.find(target) == childGridData.end()) {
		ControlGridData gData = {
			row,
			0,
			colum,
			0
		};
		childGridData.insert({ target,gData });
	}
	else {
		childGridData[target].row = row;
		childGridData[target].colum = colum;
	}
}

void Grid::setGridRCCollection(unsigned int rowCount, unsigned int columnCount) noexcept
{
	for (unsigned int i = 0; i < rowCount; ++i)
		addRowDefinition(RowDefinition());
	for (unsigned int i = 0; i < columnCount; ++i)
		addColumDefinition(ColumDefinition());
}

void Grid::Aeasure(const Size& size) noexcept
{
	//平均行高度
	float avRowHeight;
	//平均行高度的计算是实际控件高度减去固定高度总和的剩下高度由剩下的行平分
	float heigthLeft = size.Height() - totalFixedHeight;
	//如果余下高度小于0，那么就说明非固定高度的行的高度为0
	//否则就是剩余高度 / 非固定行数
	if (heigthLeft <= 0)
		avRowHeight = 0;
	else
		avRowHeight = heigthLeft / rNoneFixedNum;
	//当前高度和
	float yi = 0;
	//设置每行的高度
	for (auto& row : rowDeinitions) {
		row.y = yi;
		if (!row.validHeight) {
			row.height = avRowHeight;
			yi += avRowHeight;
			continue;
		}
		if (yi + row.height > size.Height()) {
			row.height = size.Height() - yi;
			yi = size.Height();
		}
		else {
			yi += row.height;
		}
	}

	//平均列宽度同上
	float avColumWidth;
	float widthLeft = size.Width() - totalFixedWidth;
	if (widthLeft <= 0)
		avColumWidth = 0;
	else
		avColumWidth = widthLeft / cNoneFixedNum;
	float xi = 0;
	for (auto& colum : columDeinitions) {
		colum.x = xi;
		if (!colum.validWidth) {
			colum.width = avColumWidth;
			xi += avColumWidth;
			continue;
		}
		if (xi + colum.width > size.Width()) {
			colum.width = size.Width() - xi;
			yi = size.Width();
		}
		else {
			yi += colum.width;
		}
	}
	//初始化子控件在grid下的x，y
	float x = 0;
	float y = 0;

	int rCount = rowDeinitions.Size();
	int cCount = columDeinitions.Size();
	for (auto& child : childs) {
		//初始化控件的行列数据和占几行占几列的数据
		int R = 0;
		int Rspan = 1;
		int C = 0;
		int Cspan = 1;
		//如果在行列设置集合中没有找到这个控件 或者所没有设置这个控件的行列，那么就全部设成地1行第1列的
		if (childGridData.find(child) == childGridData.end()) {
			R = 0;
			C = 0;
			Rspan = 1;
			Cspan = 1;
		}
		else {
			ControlGridData& gridPair = childGridData[child];
			R = gridPair.row;
			Rspan = gridPair.rowSpan;
			C = gridPair.colum;
			Cspan = gridPair.columSpan;
		}
	}
	//遍历所有可视化树：子控件也在可视化树中
	for (auto& child : style->visualTree) {
		//初始化控件的行列数据和占几行占几列的数据
		int R = 0;
		int Rspan = 1;
		int C = 0;
		int Cspan = 1;
		//如果在行列设置集合中没有找到这个控件 或者所没有设置这个控件的行列，那么就全部设成地1行第1列的
		if (childGridData.find(child) == childGridData.end()) {
			R = 0;
			C = 0;
			Rspan = 1;
			Cspan = 1;
		}
		else {
			ControlGridData& gridPair = childGridData[child];
			R = gridPair.row;
			Rspan = gridPair.rowSpan;
			C = gridPair.colum;
			Cspan = gridPair.columSpan;
		}

		float sizeH = 0;
		float sizeW = 0;
		//当控件不存在行的设置
		//那么将子控件的y坐标对齐size绘制空间的y,高度也设置成该数据
		if (rowDeinitions.empty()) {
			y = size.Y();
			sizeH = size.Height();
		}
		else {
			//将大于行数的数据重置为第1行
			if (R >= rCount)
				R = 0;
			//将大于行数或小于0的数据重置为1行
			if (Rspan > rCount || Rspan <= 0)
				Rspan = 1;
			for (int count = R; count < R + Rspan; ++count) {
				sizeH += rowDeinitions[count].height;
			}
			y = rowDeinitions[R].y;
		}
		//如果列设置为空，同上
		if (columDeinitions.empty()) {
			x = size.X();
			sizeW = size.Width();
		}
		else {
			if (C >= cCount)
				C = 0;
			if (Cspan > cCount || Cspan <= 0)
				Cspan = 1;
			for (int count = C; count < C + Cspan; ++count) {
				sizeW += columDeinitions[count].width;
			}
			x = columDeinitions[C].x;
		}
		Size tmp(x, y,size.Z(), sizeW, sizeH);
		tmp.SetGlobalHeight(size.GlobalHeight());
		tmp.SetGlobalWidth(size.GlobalWidth());
		tmp.TransMatrix() = style->styleData().AreaSize().TransMatrix();
		child->BeginInit(tmp);
	}
}