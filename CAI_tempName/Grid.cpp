#include "Grid.h"
#include "ControlStyle.h"
#include "Coordinate.h"
Grid::Grid() noexcept :rFixedNum(0), cFixedNum(0)
{
	name = "Grid";
}

Grid::~Grid() noexcept
{

}

void Grid::addRowDefinition(const RowDefinition& rowDefine)
{
	rowDeinitions.addChild(rowDefine);
	RowDefinition& last = rowDeinitions.last();
	if (!rowDefine.height.isInvalid()) {
		if (totalFixedHeight >= height.get()) {
			last.setActualHeight(0);
		}
		else {
			float tmp = totalFixedHeight + rowDefine.height.get();
			if (tmp > height.get()) {
				last.setActualHeight(height.get() - totalFixedHeight);
				totalFixedHeight = height.get();
			}
			else {
				last.setActualHeight(last.height.get());
				totalFixedHeight += rowDefine.height.get();
			}
		}

	}
	else {
		rFixedNum++;
	}

}

void Grid::addColumDefinition(const ColumDefinition& columDefine)
{
	columDeinitions.addChild(columDefine);
	ColumDefinition& last = columDeinitions.last();
	if (!columDefine.width.isInvalid()) {
		if (totalFixedWidth >= width.get()) {
			last.setActualWidth(0);
		}
		else {
			float tmp = totalFixedWidth + columDefine.width.get();
			if (tmp > width.get()) {
				last.setActualWidth(width.get() - totalFixedWidth);
				totalFixedWidth = width.get();
			}
			else {
				last.setActualWidth(last.width.get());
				totalFixedWidth += columDefine.width.get();
			}
		}

	}
	else {
		cFixedNum++;
	}
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

void Grid::aeasure(const Size& size) noexcept
{
	//ƽ���и߶�
	float avRowHeight;
	//ƽ���и߶ȵļ����Ǽ�ȥ�̶��߶��ܺ͵�ʣ�¸߶���ʣ�µ���ƽ��
	float heigthLeft = height.get() - totalFixedHeight;
	//������ڱ߿���ôʣ�µĸ߶Ȼ�Ҫ��ȥ2���߿��С
	if (!borderSize.isInvalid())
		heigthLeft -= 2 * borderSize.get();
	if (heigthLeft <= 0)
		avRowHeight = 0;
	else
		avRowHeight = heigthLeft / rFixedNum;
	float yi = 0;
	for (auto& row : rowDeinitions) {
		if (row.height.isInvalid())
			row.setActualHeight(avRowHeight);
		row.y = yi;
		yi += avRowHeight;
	}

	//ƽ���п��ͬ��
	float avColumWidth;
	float widthLeft = width.get() - totalFixedWidth;
	if (!borderSize.isInvalid())
		widthLeft -= 2 * borderSize.get();
	if (widthLeft <= 0)
		avColumWidth = 0;
	else
		avColumWidth = widthLeft / cFixedNum;
	float xi = 0;
	for (auto& colum : columDeinitions) {
		if (colum.width.isInvalid())
			colum.setActualWidth(avColumWidth);
		colum.x = xi;
		xi += avColumWidth;
	}
	//��ʼ���ӿؼ���grid�µ�x��y
	float x = 0;
	float y = 0;

	int rCount = rowDeinitions.Size();
	int cCount = columDeinitions.Size();
	//�������п��ӻ������ӿؼ�Ҳ�ڿ��ӻ�����
	for (auto& child : style->visualTree) {
		//��ʼ���ؼ����������ݺ�ռ����ռ���е�����
		int R = 0;
		int Rspan = 1;
		int C = 0;
		int Cspan = 1;
		//������������ü�����û���ҵ�����ؼ� ������û����������ؼ������У���ô��ȫ����ɵ�1�е�1�е�
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
		//���ؼ��������е�����
		//��ô���ӿؼ���y�������size���ƿռ��y,�߶�Ҳ���óɸ�����
		if (rowDeinitions.empty()) {
			y = size.Y();
			sizeH = size.Height();
		}
		else {
			//��������������������Ϊ��1��
			if (R >= rCount)
				R = 0;
			//������������С��0����������Ϊ1��
			if (Rspan > rCount || Rspan <= 0)
				Rspan = 1;
			for (int count = R; count < R + Rspan; ++count) {
				sizeH += rowDeinitions[count].getActualHeight();
			}
			y = rowDeinitions[R].y;
		}
		//���������Ϊ�գ�ͬ��
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
				sizeW += columDeinitions[count].getActualWidth();
			}
			x = columDeinitions[C].x;
		}
		
		Size tmp(x, y,size.Z(), sizeW, sizeH);
		tmp.TransMatrix() = style->styleData().AreaSize().TransMatrix();
		child->beginInit(tmp);
	}
}
