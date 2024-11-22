#pragma once
#include"Object.h"
#include"Mathmatics/Math.hpp"

class Point : public Object {
public:
	Point() noexcept :x(0.f), y(0.f) {}
	Point(std::initializer_list<float> list) { if (list.size() != 2) { x = 0.f; y = 0.f; return; } auto it = list.begin(); x = *it; y = *(++it); }
	Point(float x, float y) noexcept :x(x), y(y) {}
	Point(Point&& p) noexcept :x(0.f), y(0.f) { swap(std::move(p)); }
	Point(const Point& p) noexcept { x = p.x; y = p.y; }
	~Point() noexcept {}
public:
	static void TranslatTo(Point& pt, const Math::TransMatrix& trans) {
		Math::vec4 tmp = { pt.x,pt.y,1,1 };
		Math::vec4 newValue = trans * tmp;
		pt.x = newValue[0][0];
		pt.y = newValue[1][0];
	}
	static void SetToLeftBottom(Point& globalpt, float height) {
		globalpt.y = height - globalpt.y;
	}
	static void SetOriginTo(Point& globalpt, const Point& newOrigin) {
		globalpt.x = -(newOrigin.x - globalpt.x);
		globalpt.y = newOrigin.y - globalpt.y;
	}
public:
	float& X() const { return x; }
	float& Y() const { return y; }

public:
	inline void swap(Point&& p) { x = p.x; y = p.y; }
	Point operator+(const Point& p) noexcept { Point tmp(*this); tmp.x += p.x; tmp.y += p.y; return tmp; }
	Point& operator=(Point&& p) noexcept { swap(std::move(p)); return *this; }
	Point& operator=(const Point& p) noexcept { x = p.x; y = p.y; return *this; }
	bool operator==(const Point& p) { return x == p.x && y == p.y; }
private:
	mutable float x;
	mutable float y;
};

class Size : public Object {
public:
	Size() noexcept : width(0.f), height(0.f),globalWidth(0.f),globalHeight(0.f), x(0.f), y(0.f), z(0.f) {
		invalid = true;
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = 1;
		sizeCoord[3][0] = 1;
	}
	Size(const Point& point, float width, float height) noexcept :width(width), height(height), globalWidth(0.f), globalHeight(0.f), x(point.X()), y(point.Y()),z(0.f){
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = 1;
		sizeCoord[3][0] = 1;
	}
	Size(float x, float y, float z,float width, float height) noexcept : width(width), height(height), globalWidth(0.f), globalHeight(0.f), x(x), y(y),z(z){
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = z;
		sizeCoord[3][0] = 1;
	}
	Size(const Size& other) noexcept {
		width = other.width;
		height = other.height;
		globalHeight = other.globalHeight;
		globalWidth = other.globalWidth;
		x = other.x;
		y = other.y;
		z = other.z;
		mode = other.mode;
		sizeCoord = other.sizeCoord;
	}
public:
	void setX(float value) { x = value; sizeCoord[0][0] = x; }
	void setY(float value) { y = value; sizeCoord[1][0] = y; }
	void setZ(float value) { z = value; sizeCoord[2][0] = z; }
	void SetGlobalWidth(float value)  {  globalWidth = value; }
	void SetGlobalHeight(float value)  {  globalHeight = value; }
	void setCoordinat(float x, float y) { this->x = x; this->y = y; sizeCoord[0][0] = x; sizeCoord[1][0] = y; }
	void setCoordinat(float x, float y, float z) { this->x = x; this->y = y;  this->z = z; sizeCoord[0][0] = x; sizeCoord[1][0] = y; sizeCoord[2][0] = z; }
	void setCoordinat(Math::vec4& vec) { 
		sizeCoord = vec;
		this->x = sizeCoord[0][0];
		this->y = sizeCoord[1][0];
		this->z = sizeCoord[2][0];
	}
	float X() const { return x; }
	float Y() const { return y; }
	float Z() const { return z; }
	float GlobalWidth() const{ return globalWidth; }
	float GlobalHeight() const { return globalHeight; }
	float Width() const { return width; }
	float Height() const { return height; }
	Math::TransMatrix& TransMatrix() const { return mode; }
	Math::vec4& Coordinate() const{ return sizeCoord; }
	void SetWidth(const float value) { width = value; }
	void SetHeight(const float value) { height = value; }
	bool PointIn(const float& x, const float& y) const{
		return (x >= this->x && x <= this->x + width) && (y >= this->y && y <= this->y + height);
	}
public:
	Size& operator=(const Size& other) {
		width = other.width;
		height = other.height;
		globalHeight = other.globalHeight;
		globalWidth = other.globalWidth;
		x = other.x;
		y = other.y;
		z = other.z;
		mode = other.mode;
		sizeCoord = other.sizeCoord;
		return *this;
	}
private:
	friend class VisualData;
	//���ӻ��Ŀռ���
	float width;
	//���ӻ��Ŀռ�߶�
	float height;
	float globalWidth;
	float globalHeight;
	//�ֲ�����X���ռ����Ͻ�
	float x;
	//�ֲ�����Y���ռ����Ͻ�
	float y;
	float z;
	//ģ�;���--���ڽ����������ת����ȫ������
	mutable Math::TransMatrix mode;
	//��x,y,z��ɵĶ�������----ͼ�����ϽǵĶ�������
	mutable Math::vec4 sizeCoord;
};