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
	inline Size& ContentSize() const noexcept { return *contentSize; }
	inline Draw::Brush& AreaBrush() const noexcept { return *areaBrush; }
	inline unsigned int VertexSize() const noexcept { return vertexSize; }
	inline unsigned int IndexSize() const noexcept { return indexSize; }
	void setBorderSize(float value) noexcept;
	float* VertexData() const noexcept;
	void initData();
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
private:
	friend class PaintDevice;
	//绘制区域大小
	mutable Size* areaSize;
	//边框大小
	mutable float borderSize;
	//除去边框的内容大小---所有子控件将在此区域内绘制
	mutable Size* contentSize;
	//绘制区域颜色刷
	mutable Draw::Brush* areaBrush;
	mutable Draw::Brush* borderBrush;
	//绘制顶点数据
	mutable float* vertexData;
	mutable float* borderData;
	//顶点索引数据
	mutable unsigned int* vertexIndexData;

	//顶点数据个数
	mutable unsigned int vertexSize;
	//锁定数据个数
	mutable unsigned int indexSize;
	//材质ID
	mutable unsigned int texture;
};
