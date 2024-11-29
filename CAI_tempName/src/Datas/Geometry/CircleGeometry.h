#pragma once
#include "Geometry.h"
#include "Datas/Coordinate.h"
//Բ��·��
class CircleGeometry : public Geometry
{
public:
	void SetGeometry(const double& radius, const double& angle, const Point& center);
private:
	//�뾶
	double radius;
	//�Ƕ�
	double angle;
	//����
	Point center;
};

