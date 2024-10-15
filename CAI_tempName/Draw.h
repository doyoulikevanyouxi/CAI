#pragma once
#include<initializer_list>
#include<array>
#include"castd.h"
namespace Draw {
	enum Type {
		POINTS = 0x0000,
		LINES = 0x0001,		//一条线两个顶点，所以顶点=2n
		LINE_LOOP = 0x0002,
		LINE_STRIP = 0x0003,
		TRIANGLES = 0x0004,	//一个三角形三个顶点，所以顶点=3n
		SQUARE = 0x0005		//一个四边形由两个三角形组成，有6个顶点，所以顶点=6n
	};

	class Color {
	public:
		Color() noexcept : rColor(0), gColor(0), bColor(0), aColor(255) {}
		Color(Byte a, Byte r, Byte g, Byte b) noexcept:aColor(a),rColor(r),gColor(g),bColor(b){}
		explicit Color(const uint32_t& cl) noexcept { *this = cl; }
		Color(const Color& cl) noexcept { *this = cl; }
	public:
		enum {
			BLACK = 0xffffffff,
			RED = 0xffff0000,
			GREEN = 0xff00ff00,
			BLUE = 0xff0000ff
		};
	public:
		Byte& A() const noexcept{ return aColor; }
		Byte& R() const noexcept{ return rColor; }
		Byte& G() const noexcept{ return gColor; }
		Byte& B() const noexcept{ return bColor; }

		float A_f() const noexcept { return static_cast<float>(aColor); }
		float R_f() const noexcept { return static_cast<float>(rColor); }
		float G_f() const noexcept { return static_cast<float>(gColor); }
		float B_f() const noexcept { return static_cast<float>(bColor); }
	public:
		Color& operator=(uint32_t argb) {
			aColor = (0xff000000 & argb) >> 24;
			rColor = (0x00ff0000 & argb) >> 16;
			gColor = (0x0000ff00 & argb) >> 8;
			bColor = 0x000000ff & argb;
			return *this;
		}
		Color& operator=(const Color& cl) {
			aColor = cl.aColor;
			rColor = cl.rColor;
			gColor = cl.gColor;
			bColor = cl.bColor;
			return *this;
		}
	public:
		mutable Byte rColor;
		mutable Byte gColor;
		mutable Byte bColor;
		mutable Byte aColor;
	};
	class Brush {
	public:
		Brush() noexcept:bColor(Color::BLACK), bBitmap(nullptr){}
		explicit Brush(uint32_t color_v) noexcept:bBitmap(nullptr){
			bColor = color_v;
		}
		~Brush()
		{
			if (bBitmap != nullptr)
				delete[] bBitmap;
		}
		Brush(const Brush& other){
			bColor = other.bColor;
			bBitmap = nullptr;
		}
	public:
		Color& BColor() const noexcept{ return bColor; }
	public:
		Brush& operator=(const Brush& other) noexcept{
			bColor = other.bColor;
			return *this;
		}
	private:
		mutable Color bColor;
		Byte* bBitmap;
	};
}
