#include "caipch.h"
#include "CircleGeometry.h"

void CircleGeometry::SetGeometry(const double& radius, const double& angle, const Point& center)
{
	this->radius = radius;
	this->angle = angle;
	this->center = center;
}
