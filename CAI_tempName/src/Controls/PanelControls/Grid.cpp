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
	//ƽ���и߶�
	float avRowHeight;
	//ƽ���и߶ȵļ�����ʵ�ʿؼ��߶ȼ�ȥ�̶��߶��ܺ͵�ʣ�¸߶���ʣ�µ���ƽ��
	float heigthLeft = size.Height() - totalFixedHeight;
	//������¸߶�С��0����ô��˵���ǹ̶��߶ȵ��еĸ߶�Ϊ0
	//�������ʣ��߶� / �ǹ̶�����
	if (heigthLeft <= 0)
		avRowHeight = 0;
	else
		avRowHeight = heigthLeft / rNoneFixedNum;
	//��ǰ�߶Ⱥ�
	float yi = 0;
	//����ÿ�еĸ߶�
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

	//ƽ���п��ͬ��
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
	//��ʼ���ӿؼ���grid�µ�x��y
	float x = 0;
	float y = 0;

	int rCount = rowDeinitions.Size();
	int cCount = columDeinitions.Size();
	for (auto& child : childs) {
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
	}
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
				sizeH += rowDeinitions[count].height;
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