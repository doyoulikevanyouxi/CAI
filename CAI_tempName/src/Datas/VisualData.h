#pragma once
#include "Object.h"
#include "Coordinate.h"
#include "UI/Draw.h"
#include "Mathmatics/Math.hpp"
/// <summary>
/// ������һ���ؼ������л�������
/// </summary>
class VisualData:public Object {
public:
	inline  Size& AreaSize() { return areaSize; }
	inline  Size& ClipSize() { return clipSize; }
	inline bool& Visible() { return visible; }
	inline double& BorderSize() { return borderSize; }
	inline const double* VertexData() const { return &vertexPoint[0]; }
	inline const double* SizeData() const { return &rectSize[0]; }
	inline const double* VertexColorData() const { return &vertexColor[0]; }
	inline const double* RadiusData() const { return &radius[0]; }
	inline const double* BorderSizeData() const { return &borderSize; }
	inline const double* BorderColorData() const { return &borderColor[0]; }

	inline const Size& AreaSize() const { return areaSize; }
	inline const Size& ClipSize() const { return clipSize; }
	inline const bool& Visuble() const { return visible; }
	inline  const double& BorderSize() const { return borderSize; }

public:
	void SetPoint(const double& x, const double& y, const double& z);
	void SetWH(const double& width, const double& height);
	void SetAreaBrush(const Draw::Brush& brush);
	void SetBorderBursh(const Draw::Brush& brush);
	void SetBorderSize(const double& value);
	void SetClipSize(const Size& size);
	void SetRadius(const double& r1, const double& r2, const double& r3, const double& r4);
private:
	inline void UpdateVertexPoint();
	inline void UpdateRectSize();
	inline void UpdateVertexColor();
	inline void UpdateBorderColor();
private:
	//�ؼ�����---�����ؼ������Ͻ����꣬�ؼ��Ĵ�С���ؼ���ģ�;���
	Size areaSize;
	//�ü�����---���������ÿؼ�Opengl��Ⱦ���򣬳�������ĵط�������Ⱦ��Ҳ��������ѽ���Ⱦ������
	Size clipSize;
	Draw::Brush areaBrush;
	Draw::Brush borderBrush;
	bool visible = true;
	//�����������ڽ��ؼ��������ݰ󶨵�GPU��
	//�߿��С
	double borderSize;
	//��������
	std::array<double, 3> vertexPoint;
	std::array<double, 2> rectSize;
	//������ɫ
	std::array<double, 4> vertexColor;
	std::array<double, 4> radius;
	//�߿���ɫ
	std::array<double, 4> borderColor;
};
