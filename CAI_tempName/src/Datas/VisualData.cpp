#include "caipch.h"
#include "VisualData.h"
#include "UI/Draw.h"
#include <glad/glad.h>
#include "stbimge/stb_image.h"
VisualData::VisualData() noexcept :isDataHasBeenPushToGpu(false), hasBorder(false), needClip(false), borderSize(0), colorData(), originVertexData(), rectSizeData()
{
}

VisualData::VisualData(const VisualData& other) noexcept : VisualData()
{
	*this = other;
}

VisualData::~VisualData() noexcept
{
}

void VisualData::SetBorderSize(float value) noexcept
{
	if (value < 0.1)
		return;
	borderSize = value;
	hasBorder = true;
}



void VisualData::InitData()
{
	contentSize = areaSize;
	globalAreaSize.SetHeight(areaSize.height);
	globalAreaSize.SetWidth(areaSize.width);
	globalAreaSize.SetGlobalWidth(areaSize.globalWidth);
	globalAreaSize.SetGlobalHeight(areaSize.globalHeight);
	Math::vec4_t xyz = areaSize.sizeCoord.Transpose() * areaSize.mode;
	globalAreaSize.setCoordinat(xyz[0][0], xyz[0][1], xyz[0][2]);
	if (hasBorder) {
		float x = contentSize.x;
		float y = contentSize.y;
		float width = contentSize.width;
		float height = contentSize.height;
		x = x + borderSize;
		y = y + borderSize;
		width = width - 2 * borderSize;
		height = height - 2 * borderSize;
		contentSize.setX(x);
		contentSize.setY(y);
		contentSize.SetWidth(width);
		contentSize.SetHeight(height);
		bordderVertexData[0] = areaSize.x;
		bordderVertexData[1] = areaSize.y;
		bordderVertexData[2] = areaSize.z;
		//设置大小
		borderRectSizeData[0] = areaSize.width;
		borderRectSizeData[1] = areaSize.height;
		borderColorData[0] = borderBrush.BColor().R();
		borderColorData[1] = borderBrush.BColor().G();
		borderColorData[2] = borderBrush.BColor().B();
		borderColorData[3] = borderBrush.BColor().A();
	}
	//设置左上角
	originVertexData[0] = contentSize.x;
	originVertexData[1] = contentSize.y;
	originVertexData[2] = contentSize.z;
	//设置大小
	rectSizeData[0] = contentSize.width;
	rectSizeData[1] = contentSize.height;
	//设置背景色
	colorData[0] = areaBrush.BColor().R();
	colorData[1] = areaBrush.BColor().G();
	colorData[2] = areaBrush.BColor().B();
	colorData[3] = areaBrush.BColor().A();
}

