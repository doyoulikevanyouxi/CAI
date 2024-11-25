#pragma once
#include "Panel.h"
#include "Datas/RowDefinition.h"

using RowDefinitionCollection = Collection<RowDefinition>;
using ColumDefinitionCollection = Collection<ColumDefinition>;
struct ControlGridData {
	int row;
	int rowSpan;
	int colum;
	int columSpan;
};

/// <summary>
/// ���񲼾ֿؼ�������һ���ǳ�ʹ�õĿؼ���Ҳ���ǳ��õĿؼ�
/// �ò��ֿؼ���������ӵ�е�����������񻮷� 
/// </summary>
class Grid : public Panel
{
public:
	Grid() noexcept;
	virtual ~Grid() noexcept;
public:
	void addRowDefinition(const RowDefinition& rowDefine);
	void addColumDefinition(const ColumDefinition& columDefine);
	void setRow(UIElement* target, int row);
	void setRowSpan(UIElement* target, int rowSpan);
	void setColum(UIElement* target, int colum);
	void setColumSpan(UIElement* target, int columSpan);
	void setRC(UIElement* target, int row, int colum);
	void setGridRCCollection(unsigned int rowCount, unsigned int columnCount) noexcept;
protected:
	virtual void Aeasure(const Size& size) noexcept override;
public:
	RowDefinitionCollection rowDeinitions;
	ColumDefinitionCollection columDeinitions;
public:
	//AttachedProperty<std::unordered_map<UIElement*, int>> row{ "Row" };
	//AttachedProperty<std::unordered_map<UIElement*, int>> rowSpan{ "Row" };
	//AttachedProperty<std::unordered_map<UIElement*, int>> colum{ "Colum" };
	//AttachedProperty<std::unordered_map<UIElement*, int>> colum{ "Colum" };
private:
	int rNoneFixedNum;
	float totalFixedWidth;		//�����Ѿ����õĹ̶���Ⱥ�
	float totalFixedHeight;	//�����Ѿ����õĹ̶��߶Ⱥ�
	int cNoneFixedNum;
	std::unordered_map<Visual*, ControlGridData> childGridData;
};

