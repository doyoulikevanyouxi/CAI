#include "caipch.h"
#include "RectGeometry.h"

void RectGeometry::SetGeometry(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	points[3] = p4;
}
