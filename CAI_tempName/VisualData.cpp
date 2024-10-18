#include "VisualData.h"
#include "Coordinate.h"
#include "Draw.h"
#include <glad/glad.h>
#include "stb_image.h"
VisualData::VisualData() noexcept :isDataHasBeenPushToGpu(false), hasBorder(false), areaSize(new Size()), borderSize(0), contentSize(new Size()),
areaBrush(new Draw::Brush()), borderBrush(new Draw::Brush()), vertexData(new float[12]), vertexColorData(new float[16]), borderVertexData(new float[12]),
borderVertexColorData(new float[16]), textureIndexData(new float[8]), vertexIndexData(new unsigned int[6]), vertexSize(4), indexSize(6), texture(0)
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
	if (contentSize != nullptr)
		delete contentSize;
	if (areaBrush != nullptr)
		delete areaBrush;
	if (borderBrush != nullptr)
		delete borderBrush;
	if (vertexData != nullptr)
		delete[] vertexData;
	if (vertexColorData != nullptr)
		delete[] vertexColorData;
	if (borderVertexData != nullptr)
		delete[] borderVertexData;
	if (borderVertexColorData != nullptr)
		delete[] borderVertexColorData;
	if (textureIndexData != nullptr)
		delete[] textureIndexData;
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
		float vertData[12] = {
			//左上
			areaSize->x, areaSize->y,areaSize->z,
			//右上
			areaSize->x + areaSize->width, areaSize->y,areaSize->z,
			//左下
			areaSize->x, areaSize->y + areaSize->height,areaSize->z,
			//右下
			areaSize->x + areaSize->width, areaSize->y + areaSize->height, areaSize->z
		};
		memcpy(borderVertexData, vertData, sizeof(vertData));
	}

	float verData[12] = {
		//左上
		contentSize->x, contentSize->y,contentSize->z,
		//右上
		contentSize->x + contentSize->width, contentSize->y,contentSize->z,
		//左下
		contentSize->x, contentSize->y + contentSize->height,contentSize->z,
		//右下
		contentSize->x + contentSize->width, contentSize->y + contentSize->height, contentSize->z
	};
	memcpy(vertexData, verData, sizeof(verData));
	float vertColorData[16] = {
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f()
	};
	memcpy(vertexColorData, vertColorData, sizeof(vertColorData));

	float bordColorData[16] = {
		borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f(),
		borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f(),
		borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f(),
		borderBrush->BColor().R_f(), borderBrush->BColor().G_f(), borderBrush->BColor().B_f(),borderBrush->BColor().A_f()
	};
	memcpy(borderVertexColorData, bordColorData, sizeof(bordColorData));


	unsigned int tmpIndex[6] = {
		0,1,2,
		1,2,3
	};
	memcpy(vertexIndexData, tmpIndex, sizeof(tmpIndex));
	if (areaBrush->hasTexture()) {
		float textIndexData[8] = {
		0,0,
		1,0,
		0,1,
		1,1
		};
		memcpy(textureIndexData, textIndexData, sizeof(textIndexData));
	}
	else {
		float textIndexData[8] = {
		-1,-1,
		-1,-1,
		-1,-1,
		-1,-1
		};
		memcpy(textureIndexData, textIndexData, sizeof(textIndexData));
	}
	
	
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
	texture = other.texture;
	invalid = other.invalid;
	memcpy(vertexData, other.vertexData, sizeof(float) * 12);
	memcpy(vertexColorData, other.vertexColorData, sizeof(float) * 16);
	memcpy(borderVertexData, other.vertexData, sizeof(float) * 12);
	memcpy(borderVertexColorData, other.borderVertexColorData, sizeof(float) * 16);
	memcpy(textureIndexData, other.textureIndexData, sizeof(float) * 8);
	memcpy(vertexIndexData, other.vertexIndexData, sizeof(unsigned int) * 6);
	return *this;
}
