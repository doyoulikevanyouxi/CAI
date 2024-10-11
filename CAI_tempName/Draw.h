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
		Color() noexcept : colors({ 0 }), rColor(0), gColor(0), bColor(0), aColor(255) {}
		explicit Color(std::initializer_list<uint8_t> list) :Color() {
			if (list.size() == 0)
				return;
			int i = 0;
			for (std::initializer_list<uint8_t>::iterator it = list.begin(); it != list.end() && i <= 3; ++it, ++i)
			{
				colors[i] = *it;
			}
			aColor = colors[0];
			rColor = colors[1];
			gColor = colors[2];
			bColor = colors[3];
		}
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
		Color& operator=(uint32_t argb) {
			aColor =colors[0] = (0xff000000 & argb) >> 24;
			rColor = colors[1] = (0x00ff0000 & argb) >> 16;
			gColor =colors[2] = (0x0000ff00 & argb) >> 8;
			bColor = colors[3] = 0x000000ff & argb;
			return *this;
		}
		Color& operator=(const Color& cl) {
			colors[0] = aColor = cl.aColor;
			colors[1] = rColor = cl.rColor;
			colors[2] = gColor = cl.gColor;
			colors[3] = bColor = cl.bColor;
			return *this;
		}
	public:
		std::array<uint8_t, 4> colors;
		Byte rColor;
		Byte gColor;
		Byte bColor;
		Byte aColor;
	};
	class Brush {
	public:
		Brush() noexcept :mixProportion(1.0), color(Color::BLACK), bitPic(nullptr){setData();}
		explicit Brush(Color& color) noexcept :mixProportion(1.0), color(color), bitPic(nullptr) { setData(); }
		explicit Brush(uint32_t color16) noexcept :mixProportion(1.0), color(color16), bitPic(nullptr) { setData(); }
	public:
		void setMixProportion(float ratio) { mixProportion = ratio; }
		float* getData() { return drawData; }
	private:
		void setData() {
			drawData[0] = color.aColor / 255.f * mixProportion;
			drawData[1] = color.rColor / 255.f * mixProportion;
			drawData[2] = color.gColor / 255.f * mixProportion;
			drawData[3] = color.bColor / 255.f * mixProportion;
		}
	public:
		Brush& operator=(const Brush& bs) { color = bs.color; mixProportion = bs.mixProportion; for (int i = 0; i < 4; ++i)drawData[i] = bs.drawData[i]; return *this; }
		Brush& operator=(const Color& cl) { color = cl; mixProportion = 1.f;setData(); return *this; }
	private:
		//颜色或图片或二者的混合
		float mixProportion; //混合占比
		Color color;			//颜色
		Byte* bitPic;			//位图数据
	private:
		float drawData[4]{0.f};
	};
}
