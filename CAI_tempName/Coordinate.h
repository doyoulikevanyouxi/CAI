#pragma once
#include<utility>
#include"Object.h"
#include"Math.hpp"
class Point : public Object {
public:
	Point() noexcept :x(0.f), y(0.f) {}
	Point(std::initializer_list<float> list) { if (list.size() != 2) { x = 0.f; y = 0.f; return; } auto it = list.begin(); x = *it; y = *(++it); }
	Point(float x, float y) noexcept :x(x), y(y) {}
	Point(Point&& p) noexcept :x(0.f), y(0.f) { swap(std::move(p)); }
	Point(const Point& p) noexcept { x = p.x; y = p.y; }
	~Point() noexcept {}
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
	Size() noexcept : width(0.f), height(0.f), x(0.f), y(0.f),z(0.f){
		invalid = true;
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = 1;
		sizeCoord[3][0] = 1;
	}
	Size(const Point& point, float width, float height) noexcept :width(width), height(height), x(point.X()), y(point.Y()),z(0.f){
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = 1;
		sizeCoord[3][0] = 1;
	}
	Size(float x, float y, float z,float width, float height) noexcept : width(width), height(height), x(x), y(y),z(z){
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = z;
		sizeCoord[3][0] = 1;
	}
	Size(const Size& other) noexcept {
		width = other.width;
		height = other.height;
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
	void setCoordinat(float x, float y) { this->x = x; this->y = y; sizeCoord[0][0] = 0; sizeCoord[1][0] = y; }
	float X() const { return x; }
	float Y() const { return y; }
	float Z() const { return z; }
	float Width() const { return width; }
	float Height() const { return height; }
	Math::SquareMatrix<4>& TransMatrix() const { return mode; }
	void setWidth(const float value) { width = value; }
	void setHeight(const float value) { height = value; }
public:
	Size& operator=(const Size& other) {
		width = other.width;
		height = other.height;
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
	//�ֲ�����X���ռ����Ͻ�
	float x;
	//�ֲ�����Y���ռ����Ͻ�
	float y;
	float z;
	//ģ�;���--���ڽ����������ת����ȫ������
	mutable Math::TransMatrix mode;
	//��x,y��ɵ�����
	mutable Math::vec4 sizeCoord;
};