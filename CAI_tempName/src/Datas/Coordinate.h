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
	inline void SetX(const float& value) { x = value; }
	inline void SetY(const float& value) { y = value; }
	inline void SetXY(const float& valueX, const float& valueY) { x = valueX; y = valueY; }
public:
	//将点根据给定的矩阵，转换
	static void TranslatTo(Point& pt, const Math::mat4& trans) {
		Math::vec4 tmp = { pt.x,pt.y,1,1 };
		Math::vec4 newValue = trans * tmp;
		pt.x = newValue[0][0];
		pt.y = newValue[1][0];
	}
	//反转Y坐标轴
	static void Reverse(Point& pt, const float& resolutionHeight) {
		pt.y = resolutionHeight - pt.y;
	}
	//设置点到对应矩形的左下点
	static void SetToLeftBottom(Point& globalpt, float height) {
		globalpt.y = globalpt.y - height;
	}
	static void SetOriginTo(Point& globalpt, const Point& newOrigin) {
		globalpt.x = -(newOrigin.x - globalpt.x);
		globalpt.y = newOrigin.y - globalpt.y;
	}
public:
	inline float& X() { return x; }
	inline float& Y() { return y; }

	inline const float& X() const { return x; }
	inline const float& Y() const { return y; }

public:
	inline void swap(Point&& p) { x = p.x; y = p.y; }
	Point operator+(const Point& p) noexcept { Point tmp(*this); tmp.x += p.x; tmp.y += p.y; return tmp; }
	Point& operator=(Point&& p) noexcept { swap(std::move(p)); return *this; }
	Point& operator=(const Point& p) noexcept { x = p.x; y = p.y; return *this; }
	bool operator==(const Point& p) { return x == p.x && y == p.y; }
private:
	float x;
	float y;
};

class Size : public Object {
public:
	Size()noexcept :resolutionWidth(0.0), resolutionHeight(0.0), x(0.0), y(0.0), z(0.0), height(0.0), width(0.0) {}
	Size(const float& x, const float& y, const float& z, const float& width, const float& height) noexcept :resolutionWidth(0.0), resolutionHeight(0.0), x(x), y(y), z(z), height(height), width(width) {}
	~Size() = default;
	Size(const Size& other) noexcept {
		resolutionWidth = other.resolutionWidth;
		resolutionHeight = other.resolutionHeight;
		width = other.width;
		height = other.height;
		x = other.x;
		y = other.y;
		z = other.z;
		mode = other.mode;
		projection = other.projection;
		//*this = other;
	}
public:


	inline float& X() { return x; }
	inline float& Y() { return y; }
	inline float& Z() { return z; }
	inline float& Width() { return width; }
	inline float& Height() { return height; }
	inline float& ResolutionWidth() { return resolutionWidth; }
	inline float& ResolutionHeight() { return resolutionHeight; }
	inline Math::mat4& ModelMatrix() { return mode; }
	inline Math::mat4& ProjectionMatrix() { return projection; }

	inline const float& X() const { return x; }
	inline const float& Y() const { return y; }
	inline const float& Z() const { return z; }
	inline const float& Width()  const { return width; }
	inline const float& Height() const { return height; }
	inline const float& ResolutionWidth() const { return resolutionWidth; }
	inline const float& ResolutionHeight() const { return resolutionHeight; }
	inline const  Math::mat4& ModelMatrix() const { return mode; }
	inline const Math::mat4& ProjectionMatrix() const { return projection; }

	inline void SetX(const float& value) { x = value; }
	inline void SetY(const float& value) { y = value; }
	inline void SetZ(const float& value) { z = value; }
	inline void SetXYZ(const float& x, const float& y, const float& z) { this->x = x; this->y = y; this->z = z; }
	inline void SetWidth(const float& value) { width = value; }
	inline void SetHeight(const float& value) { height = value; }
	inline void SetWH(const float& width, const float& height) { this->width = width; this->height = height; }
	inline void SetResolution(const float& x, const float& y) { resolutionWidth = x; resolutionHeight = y; }
	bool PointIn(const float& x, const float& y) const {
		return (x >= this->x && x <= this->x + width) && (y >= this->y && y <= this->y + height);
	}
public:
	Size& operator=(const Size& other) {
		resolutionWidth = other.resolutionWidth;
		resolutionHeight = other.resolutionHeight;
		width = other.width;
		height = other.height;
		x = other.x;
		y = other.y;
		z = other.z;
		mode = other.mode;
		projection = other.projection;
		return *this;
	}
private:
	float resolutionWidth;
	float resolutionHeight;
	//局部坐标X，空间左上角
	float x;
	//局部坐标Y，空间左上角
	float y;
	float z;
	//可视化的空间宽度
	float width;
	//可视化的空间高度
	float height;
	//模型矩阵--用于将自身的坐标转换成全局坐标
	Math::mat4 mode;
	//投影矩阵
	Math::mat4 projection;
};