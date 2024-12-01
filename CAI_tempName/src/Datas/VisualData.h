#pragma once
#include "Object.h"
#include "Coordinate.h"
#include "UI/Draw.h"
#include "Mathmatics/Math.hpp"
/// <summary>
/// 包含了一个控件的所有绘制数据
/// </summary>
class VisualData:public Object {
public:
	inline Size& AreaSize() { return areaSize; }
	inline Size& ClipSize() { return clipSize; }
	inline Size& ContentSize() { return contentSize; }
	inline bool& Visible() { return visible; }
	inline float& BorderSize() { return borderSize; }
	inline const float* VertexData() const { return &vertexPoint[0]; }
	inline const float* SizeData() const { return &rectSize[0]; }
	inline const float* VertexColorData() const { return &vertexColor[0]; }
	inline const float* RadiusData() const { return &radius[0]; }
	inline const float* BorderSizeData() const { return &borderSize; }
	inline const float* BorderColorData() const { return &borderColor[0]; }

	inline const Size& AreaSize() const { return areaSize; }
	inline const Size& ClipSize() const { return clipSize; }
	inline const Size& ContentSize() const { return contentSize; }
	inline const bool& Visuble() const { return visible; }
	inline const float& BorderSize() const { return borderSize; }

public:
	void SetPoint(const float& x, const float& y, const float& z);
	void SetWH(const float& width, const float& height);
	void SetModel(const Math::mat4& model);
	void SetProjection(const Math::mat4& projection);
	void SetResolution(const float& width, const float height);
	void SetAreaBrush(const Draw::Brush& brush);
	void SetBorderBursh(const Draw::Brush& brush);
	void SetBorderSize(const float& value);
	void SetClipSize(const Size& size);
	void SetRadius(const float& r1, const float& r2, const float& r3, const float& r4);
private:
	inline void UpdateVertexPoint();
	inline void UpdateRectSize();
	inline void UpdateVertexColor();
	inline void UpdateBorderColor();
private:
	//控件区域---包含控件的左上角坐标，控件的大小，控件的模型矩阵
	Size areaSize;
	//裁剪区域---该区域设置控件Opengl渲染区域，超出区域的地方不会渲染，也不会清除已近渲染的像素
	Size clipSize;
	
	Size contentSize;
	Draw::Brush areaBrush;
	Draw::Brush borderBrush;
	bool visible = true;
	//以下内容用于将控件区域数据绑定到GPU中
	//边框大小
	float borderSize;
	//顶点数据
	std::array<float, 3> vertexPoint;
	std::array<float, 2> rectSize;
	//顶点颜色
	std::array<float, 4> vertexColor;
	std::array<float, 4> radius;
	//边框颜色
	std::array<float, 4> borderColor;
};
