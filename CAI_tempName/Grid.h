#pragma once
#include "Panel.h"
#include "RowDefinition.h"
#include <unordered_map>
using RowDefinitionCollection = Collection<RowDefinition>;
using ColumDefinitionCollection = Collection<ColumDefinition>;
/// <summary>
/// 网格布局控件，这是一个非常使用的控件，也将是常用的控件
/// 该布局控件将自身所拥有的区域进行网格划分 
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

