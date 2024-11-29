#pragma once
#include "Controls/EControl.h"
#include "Datas/Geometry/Geometry.h"
class Shape : public Control
{
public:
	void Render() override;
private:
	Geometry data;
};

