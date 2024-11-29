#pragma once
#include "Geometry.h"
#include <Datas/Coordinate.h>
class RectGeometry :	public Geometry
{
public:
	void SetGeometry(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
private:
	std::array<Point,4> points;
};

