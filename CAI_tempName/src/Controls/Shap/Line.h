#pragma once
#include "Shape.h"
#include "Datas/Geometry/LineGeometry.h"
class Line : public Shape
{
public:
	Line() noexcept;
	~Line() noexcept = default;
public:
	void Render() override;
public:
	void SetLineThickness(const float& value);
	void SetStart(const float& x, const float& y);
	void SetEnd(const float& x, const float& y);
	void SetPoint(const float x1, const float& y1, const float x2, const float& y2);
private:
	void CaculatWidthAndHeight();
private:
	LineGeometry lineData;
	float lineThickness;
private:
};

