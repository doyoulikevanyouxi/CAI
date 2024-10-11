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
	Size() noexcept : width(0.f), height(0.f),x(0.f),y(0.f),dph(0.f),dpw(0.f) {
		invalid = true; 
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = 1;
		sizeCoord[3][0] = 1;
	}
	Size(const Point& point, float width, float height,float dph,float dpw) noexcept :width(width), height(height), x(point.X()), y(point.Y()), dph(dph), dpw(dpw) {
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = 1;
		sizeCoord[3][0] = 1;
	}
	Size(float x, float y, float width, float height, float dph, float dpw) noexcept : width(width), height(height), x(x), y(y) ,dph(dph),dpw(dpw){
		sizeCoord[0][0] = x;
		sizeCoord[1][0] = y;
		sizeCoord[2][0] = 1;
		sizeCoord[3][0] = 1;
	}
public:
	void trans() noexcept {
		sizeCoord = standarMatrix * sizeCoord;
		x = sizeCoord[0][0];
		y = -sizeCoord[1][0];
		height *= dph;
		width *= dpw;
	}
	void setX(float value) { x = value; sizeCoord[0][0] = x; }
	void setY(float value) { y = value; sizeCoord[1][0] = y; }
	float& DPH() const { return dph; }
	float& DPW() const { return dpw; }
	void setCoordinat(float x, float y) { this->x = x; this->y = y; sizeCoord[0][0] = 0; sizeCoord[1][0] = y; }
	const float& X() const { return x; }
	const float& Y() const { return y; }
	float& Width() const { return width; }
	float& Height() const { return height; }
	Math::SquareMatrix<4>& TransMatrix() const { return standarMatrix; }
	void setWidth(const float value) { width = value; }
	void setHeight(const float value) { height = value; }
private:
	friend class VisualData;
	mutable float width;
	mutable float height;
	float x;
	float y;
	mutable float dph;
	mutable float dpw;
	//标准矩阵--该矩阵用于将数据从自有坐标系变换成Opengl的坐标系
	mutable Math::SquareMatrix<4> standarMatrix;
	mutable Math::vec4 sizeCoord;
};