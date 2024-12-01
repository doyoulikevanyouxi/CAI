#include "caipch.h"
#include "VisualData.h"

void VisualData::SetPoint(const float& x, const float& y, const float& z)
{	
	areaSize.SetXYZ(x, y, z);
	UpdateVertexPoint();
}

void VisualData::SetWH(const float& width, const float& height)
{
	areaSize.SetWH(width, height);
	UpdateRectSize();
}

void VisualData::SetAreaBrush(const Draw::Brush& brush)
{
	areaBrush = brush;
	UpdateVertexColor();
}

void VisualData::SetBorderBursh(const Draw::Brush& brush)
{
	borderBrush = brush;
	UpdateBorderColor();
}

void VisualData::SetBorderSize(const float& value)
{
	borderSize = value;
}

void VisualData::SetClipSize(const Size& size)
{
	clipSize = size;
}

void VisualData::SetRadius(const float& r1, const float& r2, const float& r3, const float& r4)
{
	radius[0] = r1;
	radius[1] = r2;
	radius[2] = r3;
	radius[3] = r4;
}

inline void VisualData::UpdateVertexPoint()
{
	vertexPoint[0] = areaSize.X();
	vertexPoint[1] = areaSize.Y();
	vertexPoint[2] = areaSize.Z();
}

inline void VisualData::UpdateRectSize()
{
	rectSize[0] = areaSize.Width();
	rectSize[1] = areaSize.Height();
}

inline void VisualData::UpdateVertexColor()
{
	vertexColor[0] = areaBrush.BColor().R();
	vertexColor[1] = areaBrush.BColor().G();
	vertexColor[2] = areaBrush.BColor().B();
	vertexColor[3] = areaBrush.BColor().A();
}

inline void VisualData::UpdateBorderColor()
{
	borderColor[0] = borderBrush.BColor().R();
	borderColor[3] = borderBrush.BColor().A();
	borderColor[1] = borderBrush.BColor().G();
	borderColor[2] = borderBrush.BColor().B();
}
