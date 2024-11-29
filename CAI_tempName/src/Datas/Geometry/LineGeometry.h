#pragma once
#include "Geometry.h"
#include "Datas/Coordinate.h"
#include "Datas/Coordinate.h"
class LineGeometry : public Geometry
{
public:
	//��ӵ�
	//void AddPoint(const Point& point);
	inline const Point& GetFirstPoint() const { return firstPoint; }
	inline const Point& GetSecondPoint() const { return secondPoint; }
	inline void SetFirstPoint(const Point& point) { firstPoint = point; }
	inline void SetSecondPoint(const Point& point) { secondPoint = point; }
protected:
	Point firstPoint;
	Point secondPoint;
};

