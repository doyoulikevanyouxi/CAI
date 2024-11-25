#include "caipch.h"
#include "VisualData.h"
#include "Coordinate.h"
#include "UI/Draw.h"
#include <glad/glad.h>
#include "stbimge/stb_image.h"
VisualData::VisualData() noexcept :isDataHasBeenPushToGpu(false), hasBorder(false), needClip(false), areaSize(new Size()), globalAreaSize(new Size()), borderSize(0),
																		contentSize(new Size()),clipSize(new Size()),areaBrush(new Draw::Brush()), borderBrush(new Draw::Brush()),
																		vertexData(new double[12]), vertexColorData(new double[16]), borderVertexData(new double[12]),
																		borderVertexColorData(new double[16]), textureIndexData(new double[8]), vertexIndexData(new unsigned int[6]),
																		vertexSize(4), indexSize(6), texture(0),textureBorder(0)
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
	if (clipSize != nullptr)
		delete clipSize;
	if (globalAreaSize != nullptr)
		delete globalAreaSize;
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

void VisualData::SetBorderSize(double value) noexcept
{
	if (value < 0.1)
		return;
	borderSize = value;
	hasBorder = true;
}



void VisualData::InitData()
{
	*contentSize = *areaSize;
	globalAreaSize->SetHeight(areaSize->height);
	globalAreaSize->SetWidth(areaSize->width);
	globalAreaSize->SetGlobalWidth(areaSize->globalWidth);
	globalAreaSize->SetGlobalHeight(areaSize->globalHeight);
	Math::vec4_t xyz = areaSize->sizeCoord.Transpose()* areaSize->mode;
	globalAreaSize->setCoordinat(xyz[0][0],xyz[0][1],xyz[0][2]);
	if (hasBorder) {
		double x = contentSize->x;
		double y = contentSize->y;
		double width = contentSize->width;
		double height = contentSize->height;
		x = x + borderSize;
		y = y + borderSize;
		width = width - 2 * borderSize;
		height = height - 2 * borderSize;
		contentSize->setX(x);
		contentSize->setY(y);
		contentSize->SetWidth(width);
		contentSize->SetHeight(height);
		double vertData[12] = {
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

	double verData[12] = {
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
	double vertColorData[16] = {
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f(),
		areaBrush->BColor().R_f(), areaBrush->BColor().G_f(), areaBrush->BColor().B_f(),areaBrush->BColor().A_f()
	};
	memcpy(vertexColorData, vertColorData, sizeof(vertColorData));

	double bordColorData[16] = {
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
	if (areaBrush->HasTexture()) {
		double textIndexData[8] = {
		0,0,
		1,0,
		0,1,
		1,1
		};
		memcpy(textureIndexData, textIndexData, sizeof(textIndexData));
	}
	else {
		double textIndexData[8] = {
		-1,-1,
		-1,-1,
		-1,-1,
		-1,-1
		};
		memcpy(textureIndexData, textIndexData, sizeof(textIndexData));
	}
	
	
}

double* VisualData::VertexData() const noexcept
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
	*clipSize = *(other.clipSize);
	*globalAreaSize = *(other.globalAreaSize);
	*areaBrush = *(other.areaBrush);
	vertexSize = other.vertexSize;
	indexSize = other.indexSize;
	texture = other.texture;
	invalid = other.invalid;
	memcpy(vertexData, other.vertexData, sizeof(double) * 12);
	memcpy(vertexColorData, other.vertexColorData, sizeof(double) * 16);
	memcpy(borderVertexData, other.vertexData, sizeof(double) * 12);
	memcpy(borderVertexColorData, other.borderVertexColorData, sizeof(double) * 16);
	memcpy(textureIndexData, other.textureIndexData, sizeof(double) * 8);
	memcpy(vertexIndexData, other.vertexIndexData, sizeof(unsigned int) * 6);
	return *this;
}
