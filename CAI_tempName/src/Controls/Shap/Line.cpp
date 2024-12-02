#include "caipch.h"
#include "Line.h"
#include "UI/PaintDeivces/PaintDevice.h"
Line::Line() noexcept :lineThickness(2.0)
{
	vData.SetAreaBrush(0xff000000);
}
void Line::Render()
{
	pDevice->DrawLine(vData, lineData, lineThickness);
}

void Line::SetLineThickness(const float& value)
{
	lineThickness = value;

	CaculatWidthAndHeight();

}

void Line::SetStart(const float& x, const float& y)
{
	lineData.SetStart(x, y);
	CaculatWidthAndHeight();
}

void Line::SetEnd(const float& x, const float& y)
{
	lineData.SetEnd(x, y);
	CaculatWidthAndHeight();
}

void Line::SetPoint(const float x1, const float& y1, const float x2, const float& y2)
{
	SetStart(x1, y1);
	SetEnd(x2, y2);
}

void Line::CaculatWidthAndHeight()
{
	if (lineData.StartPoint().X() == lineData.EndPoint().X() && lineData.StartPoint().Y() == lineData.EndPoint().Y()) {
		SetWidthAndHeight(0, 0);
		return;
	}
	if (lineData.StartPoint().X() == lineData.EndPoint().X()) {
		SetWidth(lineThickness);
		SetHeight(abs(lineData.StartPoint().Y() - lineData.EndPoint().Y()));
		return;
	}
	if (lineData.StartPoint().Y() == lineData.EndPoint().Y()) {
		SetHeight(lineThickness);
		SetWidth(abs(lineData.StartPoint().X() - lineData.EndPoint().X()));
		return;
	}
	float width = abs(lineData.StartPoint().X() - lineData.EndPoint().X());
	float height = abs(lineData.StartPoint().Y() - lineData.EndPoint().Y());
	SetWidthAndHeight(width, height);
}
