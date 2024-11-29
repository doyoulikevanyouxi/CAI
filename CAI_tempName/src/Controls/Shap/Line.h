#pragma once
#include "Shape.h"
#include "Datas/Geometry/LineGeometry.h"
class Line : public Shape
{
public:
	void Render() override;
public:
	inline void SetStart(const double& x, const double& y);
	inline void SetEnd(const double& x, const double& y);
	void SetPoint(const double x1, const double& y1, const double x2, const double& y2);
private:
	double x1, y1;
	double x2, y2;
	LineGeometry lineData;
};

