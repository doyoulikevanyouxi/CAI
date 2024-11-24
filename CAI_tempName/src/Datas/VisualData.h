#pragma once
#include "Object.h"
#include "Datas/Coordinate.h"
#include "UI/Draw.h"
/// <summary>
/// 包含了一个控件的所有绘制数据
/// </summary>
class VisualData final : public Object {
public:
	VisualData() noexcept;
	VisualData(const VisualData& other) noexcept;
	//VisualData(VisualData&& other) noexcept;
	~VisualData()	noexcept;
public:
	inline Size& AreaSize()  noexcept { return areaSize; }
	inline Size& ClipSize()  noexcept { return clipSize; }
	inline Size& ContentSize()  noexcept { return contentSize; }
	inline Size& GlobalAreaSize()  noexcept { return globalAreaSize; }
	inline Draw::Brush& AreaBrush()  noexcept { return areaBrush; }
	void SetBorderSize(float value) noexcept;
	void InitData();
public:
	bool isDataHasBeenPushToGpu;
	bool hasBorder;
	bool needClip;
private:
	friend class PaintDevice;
	friend class UIElement;
	friend class Control;
	//绘制区域大小
	Size areaSize;
	//边框大小
	float borderSize;
	//除去边框的内容大小---所有子控件将在此区域内绘制
	Size contentSize;
	//裁减空间---只绘制该区域的内容，超出该区域的内容将不会处理
	Size clipSize;
	Size globalAreaSize;
	//绘制区域颜色刷
	Draw::Brush areaBrush;
	Draw::Brush borderBrush;
	//矩形数据左上角坐标
	float originVertexData[3];
	float bordderVertexData[3];
	//矩形大小数据
	float rectSizeData[2];
	float borderRectSizeData[2];
	//顶点颜数据
	float borderColorData[4];
	float colorData[4];
	
	//边框的绘制数据--实际上边框的绘制数据是控件整个Size，本程序采用模板测试来丢弃内容区域的绘制
	//边框的绘制可以衍生控件阴影的绘制---但要注意文字这个东西，因为采用模板来丢弃会导致文字也能够产生阴影效果，如果不想文字也有阴影那么需要特殊处理文字渲染这块

	//顶点数据个数
	//unsigned int vertexSize;
	//索引数据个数
	//unsigned int indexSize;
	//暂时不管纹理，如果有纹理需要采用不同的着色器
	////content的纹理ID
	//unsigned int texture;
	////边框的纹理ID
	//unsigned int textureBorder;
};
