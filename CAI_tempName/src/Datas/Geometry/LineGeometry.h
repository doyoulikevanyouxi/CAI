#pragma once
#include "Geometry.h"
#include "Datas/Coordinate.h"
#include "Datas/Coordinate.h"
class LineGeometry : public Geometry
{
public:
	inline Point& StartPoint() { return startPoint; }
	inline Point& EndPoint() { return endPoint; }
	inline const Point& StartPoint() const { return startPoint; }
	inline const Point& EndPoint() const { return endPoint; }
	inline void SetStart(const float& x, const float& y) { startPoint.SetXY(x, y); }
	inline void SetEnd(const float& x, const float& y) { endPoint.SetXY(x, y); }
protected:
	Point startPoint;
	Point endPoint;
};

