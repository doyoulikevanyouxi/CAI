#pragma once
#include "Object.h"
#include "Coordinate.h"
#include "Draw.h"
#include "Math.hpp"
#include<vector>
#include<array>

class VisualData final: public Object {
public:
	VisualData() noexcept
	{ 
		invalid = true;
		name = "VisualData"; 
	}
	~VisualData() noexcept{}
public:
	size_t dataSize() const { return data.size(); }
	size_t dataIndexSize() const { return dataIndex.size(); }
	const float* Data() const { return &data.front(); }
	const unsigned* DataIndex() const { return &dataIndex.front(); }
	void setInvalid(bool isInvalid) noexcept { invalid = isInvalid; }
	void setData(Size& size,Draw::Brush& brush, Draw::Type type=Draw::TRIANGLES) {
		size.trans();
		float dataf[24] = {
			size.x,size.y,1.f,brush.getData()[1],brush.getData()[2],brush.getData()[3],
			size.x+size.width,size.y,1.f,brush.getData()[1],brush.getData()[2],brush.getData()[3],
			size.x,size.y-size.height,1.f,brush.getData()[1],brush.getData()[2],brush.getData()[3],
			size.x+size.width,size.y-size.height,1.f,brush.getData()[1],brush.getData()[2],brush.getData()[3],
		};
		unsigned int daIndex[6] = {
			0,1,2,
			1,2,3
		};
		data.assign(dataf, dataf + 24);
		dataIndex.assign(daIndex, daIndex + 6);
		invalid = false;
	}
	void test() {
		float dataf[24] = {
			-0.5,0.5,1.f,0.5,0.f,0.f,
			0.5,0.5,1.f,0.5,0.f,0.f,
			-0.5,-0.5,1.f,0.5,0.f,0.f,
			0.5,-0.5,1.f,0.5,0.f,0.f,
		};
		unsigned int daIndex[6] = {
			0,1,2,
			1,2,3
		};
		data.assign(dataf, dataf + 24);
		dataIndex.assign(daIndex, daIndex + 6);
		invalid = false;
	}
private:
	std::vector<float> data;
	std::vector<unsigned int> dataIndex;
};
