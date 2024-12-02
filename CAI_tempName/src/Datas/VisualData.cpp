#include "caipch.h"
#include "VisualData.h"

void VisualData::SetPoinX(const float& value)
{
	areaSize.SetX(value);
	contentSize.SetX(value + borderSize);
	vertexPoint[0] = value;
}

void VisualData::SetPoinY(const float& value)
{
	areaSize.SetY(value);
	contentSize.SetY(value + borderSize);
	vertexPoint[1] = value;
}

void VisualData::SetPoinZ(const float& value)
{
	areaSize.SetZ(value);
	contentSize.SetZ(value);
	vertexPoint[2] = value;
}

void VisualData::SetPoint(const float& x, const float& y, const float& z)
{	
	areaSize.SetXYZ(x, y, z);
	contentSize.SetXYZ(x+borderSize,y+borderSize,z);
	UpdateVertexPoint();
}

void VisualData::SetWidth(const float& value)
{
	areaSize.SetWidth(value);
	contentSize.SetWidth(value - 2.0 * borderSize);
	rectSize[0] = value;
}

void VisualData::SetHeight(const float& value)
{
	areaSize.SetHeight(value);
	contentSize.SetHeight(value - 2.0 * borderSize);
	rectSize[1] = value;
}

void VisualData::SetWH(const float& width, const float& height)
{
	areaSize.SetWH(width, height);
	contentSize.SetWH(width - 2.0 * borderSize, height - 2.0 * borderSize);
	UpdateRectSize();
}

void VisualData::SetModel(const Math::mat4& model)
{
	areaSize.ModelMatrix() = model;
	contentSize.ModelMatrix() = model;
}

void VisualData::SetProjection(const Math::mat4& projection)
{
	areaSize.ProjectionMatrix() = projection;
	contentSize.ProjectionMatrix() = projection;
}

void VisualData::SetResolution(const float& width, const float height)
{
	areaSize.SetResolution(width, height);
	contentSize.SetResolution(width, height);
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
	contentSize.SetXYZ(areaSize.X() + value, areaSize.Y() + value, areaSize.Z());
	contentSize.SetWH(areaSize.Width() - 2.0 * value, areaSize.Height() - 2.0 * value);
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
