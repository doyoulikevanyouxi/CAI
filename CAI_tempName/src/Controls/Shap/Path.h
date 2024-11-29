#pragma once
#include "Shape.h"
#include "Datas/Geometry/LineGeometry.h"
class Path : public Shape
{
public:
	void AddPoint(const double& x,const double& y);
private:
	LineGeometry lineGeometry;
};

