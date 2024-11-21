#pragma once
#include "Object.h"
class Size;
namespace Draw {
	class Brush;
}
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
	inline Size& AreaSize() const noexcept { return *areaSize; }
	inline Size& ClipSize() const noexcept { return *clipSize; }
	inline Size& ContentSize() const noexcept { return *contentSize; }
	inline Draw::Brush& AreaBrush() const noexcept { return *areaBrush; }
	inline unsigned int VertexSize() const noexcept { return vertexSize; }
	inline unsigned int IndexSize() const noexcept { return indexSize; }
	void SetBorderSize(float value) noexcept;
	float* VertexData() const noexcept;
	void InitData();
	unsigned int* VertexIndexData() const noexcept;

public:
	VisualData& operator=(const VisualData& other) noexcept;

	//交换两个对象的资源太麻烦了，暂时不写移动赋值
	/*VisualData& operator=(VisualData&& other) noexcept {
		areaSize = other.areaSize;
		areaBrush = other.areaBrush;
		vertexData = other.vertexData;
		vertexStride = other.vertexStride;
		colorStride = other.colorStride;
		vertexSize = other.vertexSize;
		indexSize = other.indexSize;
		invalid = other.invalid;
		other.areaSize = nullptr;
		other.areaBrush = nullptr;
		other.vertexData = nullptr;
		return *this;
	}*/
public:
	bool isDataHasBeenPushToGpu;
	bool hasBorder;
	bool needClip;
private:
	friend class PaintDevice;
	friend class UIElement;
	friend class Control;
	//绘制区域大小
	Size* areaSize;
	//边框大小
	float borderSize;
	//除去边框的内容大小---所有子控件将在此区域内绘制
	Size* contentSize;
	//裁减空间---只绘制该区域的内容，超出该区域的内容将不会处理
	Size* clipSize;
	//绘制区域颜色刷
	Draw::Brush* areaBrush;
	Draw::Brush* borderBrush;
	//绘制顶点数据
	float* vertexData;
	//顶点颜数据
	float* vertexColorData;
	//边框顶点数据
	float* borderVertexData;
	//边框顶点颜色数据
	float* borderVertexColorData;
	//纹理索引数据
	float* textureIndexData;
	//顶点索引数据
	unsigned int* vertexIndexData;
	//边框的绘制数据--实际上边框的绘制数据是控件整个Size，本程序采用模板测试来丢弃内容区域的绘制
	//边框的绘制可以衍生控件阴影的绘制---但要注意文字这个东西，因为采用模板来丢弃会导致文字也能够产生阴影效果，如果不想文字也有阴影那么需要特殊处理文字渲染这块

	//顶点数据个数
	unsigned int vertexSize;
	//索引数据个数
	unsigned int indexSize;
	//content的纹理ID
	unsigned int texture;
	//边框的纹理ID
	unsigned int textureBorder;
};
