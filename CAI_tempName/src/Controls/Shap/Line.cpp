#include "caipch.h"
#include "Line.h"
#include "UI/PaintDevice.h"
void Line::Render()
{
	pDevice->DrawLine(vData.AreaSize(), &lineData);
}

inline void Line::SetStart(const double& x, const double& y)
{
	x1 = x;
	y1 = y;
	lineData.SetFirstPoint(Point(x, y));
}

inline void Line::SetEnd(const double& x, const double& y)
{
	x2 = x;
	y2 = y;
	lineData.SetSecondPoint(Point(x, y));
}

void Line::SetPoint(const double x1, const double& y1, const double x2, const double& y2)
{
	SetStart(x1, y1);
	SetEnd(x2, y2);
}
