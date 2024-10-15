#pragma once
#include "Object.h"
class Size;
namespace Draw {
	class Brush;
}
class VisualData final : public Object {
public:
	VisualData() noexcept;
	VisualData(const VisualData& other) noexcept;
	//VisualData(VisualData&& other) noexcept;
	~VisualData()	noexcept;
public:
	inline Size& AreaSize() const noexcept { return *areaSize; }
	inline Draw::Brush& AreaBrush() const noexcept { return *areaBrush; }
	inline unsigned int VertexSize() const noexcept { return vertexSize; }
	inline unsigned int IndexSize() const noexcept { return indexSize; }
	float* VertexData() const noexcept;
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
private:
	mutable Size* areaSize;
	mutable Draw::Brush* areaBrush;
	mutable float* vertexData;
	mutable unsigned int* vertexIndexData;
	mutable int vertexStride;
	mutable int colorStride;
	mutable unsigned int vertexSize;
	mutable unsigned int indexSize;
};
