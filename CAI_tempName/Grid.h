#pragma once
#include "Panel.h"
#include "RowDefinition.h"
#include <unordered_map>
using RowDefinitionCollection = Collection<RowDefinition>;
using ColumDefinitionCollection = Collection<ColumDefinition>;
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
	void setColum(UIElement* target, int colum);
	void setRC(UIElement* target, int row, int colum);
	void setGridRCCollection(unsigned int rowCount, unsigned int columnCount) noexcept;
protected:
	virtual void aeasure(const Size& size) noexcept override;
public:
	RowDefinitionCollection rowDeinitions;
	ColumDefinitionCollection columDeinitions;
public:
	/*DependencyProperty<int> colums{ "Colums" };
	DependencyProperty<int> rows{ "Rows" };*/
	AttachedProperty<std::unordered_map<UIElement*, int>> row{ "Row" };
	AttachedProperty<std::unordered_map<UIElement*, int>> colum{ "Colum" };
private:
	int rFixedNum;
	float totalFixedWidth;
	float totalFixedHeight;
	int cFixedNum;
};

