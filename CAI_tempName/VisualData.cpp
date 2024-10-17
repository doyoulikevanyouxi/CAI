#include "VisualData.h"
#include "Coordinate.h"
#include "Draw.h"
#include <glad/glad.h>
#include "stb_image.h"
VisualData::VisualData() noexcept :isDataHasBeenPushToGpu(false), hasBorder(false), areaSize(new Size()), borderSize(0), contentSize(new Size()),
areaBrush(new Draw::Brush()), borderBrush(new Draw::Brush()), vertexData(new float[36]), borderData(new float[36]),
vertexIndexData(new unsigned int[6]), vertexSize(36),
indexSize(6), texture(0)
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
	//以下加判断是因为移动拷贝和移动赋值问题
	if (areaSize != nullptr)
		delete areaSize;
	if(contentSize != nullptr)
		delete contentSize;
	if (areaBrush != nullptr)
		delete areaBrush;
	if (vertexData != nullptr)
		delete[] vertexData;
	if (borderData != nullptr)
		delete[] borderData;
	if (vertexIndexData != nullptr)
		delete[] vertexIndexData;
}

void VisualData::setBorderSize(float value) noexcept
{
	if (value < 0.1)
		return;
	borderSize = value;
	hasBorder = true;
}



void VisualData::initData()
{
	*contentSize = *areaSize;
	if (hasBorder) {
		float x = contentSize->x;
		float y = contentSize->y;
		float width = contentSize->width;
		float height = contentSize->height;
		x = x + borderSize;
		y = y + borderSize;
		width = width - 2 * borderSize;
		height = height - 2 * borderSize;
		contentSize->setX(x);
		contentSize->setY(y);
		contentSize->setWidth(width);
		contentSize->setHeight(height);
		float bData[36] = {
					areaSize->x, areaSize->y,areaSize->z,borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f(),-1,-1,
					//右上
					areaSize->x + areaSize->width, areaSize->y, areaSize->z, borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f(),-1,-1,
					//左下
					areaSize->x, areaSize->y + areaSize->height,areaSize->z, borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f(),-1,-1,
					//右下
					areaSize->x + areaSize->width, areaSize->y + areaSize->height, areaSize->z, borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f(),-1,-1
		};
		memcpy(borderData, bData, sizeof(float) * 36);
	}

	float* tmp;
	if (!areaBrush->hasTexture()) {
		float tmp1[36] = {
			//左上
			contentSize->x, contentSize->y, contentSize->z,areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),-1,-1,
			//右上
			contentSize->x + contentSize->width, contentSize->y,contentSize->z, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),-1,-1,
			//左下
			contentSize->x, contentSize->y + contentSize->height, contentSize->z, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),-1,-1,
			//右下
			contentSize->x + contentSize->width, contentSize->y + contentSize->height,contentSize->z, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),-1,-1
		};

		tmp = tmp1;
	}
	else {
		float tmp2[36] = {
			//左上
					contentSize->x, contentSize->y,contentSize->z,areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),0,0,
					//右上
					contentSize->x + contentSize->width, contentSize->y, contentSize->z, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),1,0,
					//左下
					contentSize->x, contentSize->y + contentSize->height,contentSize->z, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),0,1,
					//右下
					contentSize->x + contentSize->width, contentSize->y + contentSize->height, contentSize->z, areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),1,1
		};
		tmp = tmp2;
	}
	unsigned int tmpIndex[6] = {
		0,1,2,
		1,2,3
	};
	//忽略此处提示，vertexData在viusaldata初始化时就已经分配了内存，除非分配失败
	memcpy(vertexData, tmp, sizeof(float) * 36);
	memcpy(vertexIndexData, tmpIndex, sizeof(unsigned int) * 6);
}

float* VisualData::VertexData() const noexcept
{
	return vertexData;
}

unsigned int* VisualData::VertexIndexData() const noexcept
{
	return vertexIndexData;
}

VisualData& VisualData::operator=(const VisualData& other) noexcept
{ 
	if (this == &other)
		return *this;
	*areaSize = *(other.areaSize);
	borderSize = borderSize;
	*contentSize = *(other.contentSize);
	*areaBrush = *(other.areaBrush);
	vertexSize = other.vertexSize;
	indexSize = other.indexSize;
	invalid = other.invalid;
	if (vertexData != nullptr) {
		memcpy(borderData, other.borderData, sizeof(float) * 36);
		memcpy(vertexData, other.vertexData, sizeof(float) * 36);
		memcpy(vertexIndexData, other.vertexIndexData, sizeof(unsigned int) * 6);
	}
	return *this;
}
