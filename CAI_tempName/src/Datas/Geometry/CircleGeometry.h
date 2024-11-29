#pragma once
#include "Geometry.h"
#include "Datas/Coordinate.h"
//圆的路径
class CircleGeometry : public Geometry
{
public:
	void SetGeometry(const double& radius, const double& angle, const Point& center);
private:
	//半径
	double radius;
	//角度
	double angle;
	//中心
	Point center;
};

