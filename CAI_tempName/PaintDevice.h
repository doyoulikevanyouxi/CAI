#pragma once
#include "Object.h"
#include "Coordinate.h"
class ControlStyle;
namespace Draw {
	class Brush;
}
class Window;
using Brush = Draw::Brush;
class PaintDevice final: public Object
{
public:
	PaintDevice() noexcept;
	PaintDevice(Window* wnd) noexcept;
	~PaintDevice() noexcept;
public:
	void setWindow(Window* wnd) noexcept;
	void setPen(const Brush& pen) noexcept;
	const Brush& getPen() const noexcept { return *pen; }
	void fillWith(Brush& bs) noexcept;
public:
	void DrawText(const std::wstring& str,const Size& size) noexcept;
	void DrawLine(const Point& initial,Point& end) noexcept;
	void DrawLines(const Point points[], size_t lineNum) noexcept;
	void DrawRect(const Point& initial, float width, float height) noexcept;
	volatile void Draw(ControlStyle* style) noexcept;
private:
	Brush* pen;
	Brush* fill;
private:
	//���ھ��
	Window* hd;
	//��������
	unsigned int VAO;
	//���㻺�����
	unsigned int VBO;
	//�����������
	unsigned int EBO;
	bool areadySet;

};

