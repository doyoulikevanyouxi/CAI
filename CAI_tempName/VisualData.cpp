#include "VisualData.h"
#include "Coordinate.h"
#include "Draw.h"
VisualData::VisualData() noexcept :areaSize(new Size()), areaBrush(new Draw::Brush()), vertexData(nullptr),
							    vertexIndexData(nullptr),vertexStride(0),colorStride(0),vertexSize(0),
								indexSize(0)
{
}

VisualData::VisualData(const VisualData& other) noexcept : VisualData()
{
	*this = other;
}

//VisualData::VisualData(VisualData&& other) noexcept
//{
//	*this = other;
//}

VisualData::~VisualData() noexcept
{
	if (areaSize != nullptr)
		delete areaSize;
	if (areaBrush != nullptr)
		delete areaBrush;
	if (vertexData != nullptr)
		delete[] vertexData;
	if (vertexIndexData != nullptr)
		delete[] vertexIndexData;
}

float* VisualData::VertexData() const noexcept
{
	if (vertexData == nullptr) {
		float tmp[24] = {
			//左上
				areaSize->x, areaSize->y, 0.f,areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),
			//右上
				areaSize->x + areaSize->width, areaSize->y, 0.f, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),
			//左下
				areaSize->x, areaSize->y + areaSize->height, 0.f, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),
			//右下
				areaSize->x + areaSize->width, areaSize->y + areaSize->height, 0.f, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f()
		};
	
		unsigned int tmpIndex[6] = {
			0,1,2,
			1,2,3
		};
		vertexData = new float[24];
		vertexIndexData = new unsigned int[6];
		vertexStride = colorStride = 6;
		vertexSize = 24;
		indexSize = 6;
		memcpy(vertexData, tmp, sizeof(float) * 24);
		memcpy(vertexIndexData, tmpIndex, sizeof(unsigned int) * 6);
	}
	return vertexData;
}

unsigned int* VisualData::VertexIndexData() const noexcept
{
	return vertexIndexData;
}

VisualData& VisualData::operator=(const VisualData& other) noexcept
{
	*areaSize = *(other.areaSize);
	*areaBrush = *(other.areaBrush);
	vertexStride = other.vertexStride;
	colorStride = other.colorStride;
	vertexSize = other.vertexSize;
	indexSize = other.indexSize;
	invalid = other.invalid;
	if (vertexData != nullptr) {
		memcpy(vertexData, other.vertexData, sizeof(float) * 24);
		memcpy(vertexIndexData, other.vertexIndexData, sizeof(unsigned int) * 6);

	}
	return *this;
	// TODO: 在此处插入 return 语句
}
