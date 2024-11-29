#pragma once
#include "UI/Draw.h"
/// <summary>
/// ����·��
/// </summary>
class Geometry
{
public:
	inline double GetSize() const { return size; }
	inline const Draw::Brush& GetBrush() const { return brush; }
protected:
	double size;
	double* data;
	Draw::Brush brush;
};

