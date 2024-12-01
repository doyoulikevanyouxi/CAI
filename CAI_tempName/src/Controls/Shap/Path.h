#pragma once
#include "Shape.h"
#include "Datas/Geometry/LineGeometry.h"
class Path : public Shape
{
public:
	void AddPoint(const float& x,const float& y);
private:
	LineGeometry lineGeometry;
};

