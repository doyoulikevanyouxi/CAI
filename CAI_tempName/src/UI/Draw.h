#pragma once

namespace Draw {
	//似乎没什么用
	enum Type {
		POINTS = 0x0000,
		LINES = 0x0001,		//一条线两个顶点，所以顶点=2n
		LINE_LOOP = 0x0002,
		LINE_STRIP = 0x0003,
		TRIANGLES = 0x0004,	//一个三角形三个顶点，所以顶点=3n
		SQUARE = 0x0005		//一个四边形由两个三角形组成，有6个顶点，所以顶点=6n
	};

	/// <summary>
	/// 颜色数据，RGBA
	/// </summary>
	class Color {
	public:
		Color() noexcept : rColor(0), gColor(0), bColor(0), aColor(255) {}
		//构造函数，参数分为是A的值，R的值，G的值，B的值
		Color(Byte a, Byte r, Byte g, Byte b) noexcept:aColor(a),rColor(r),gColor(g),bColor(b){}
		//由16进制数据直接初始化，这里并没有限制隐式转换
		Color(const uint32_t& cl) noexcept { *this = cl; }
		Color(const Color& cl) noexcept { *this = cl; }
	public:
		//默认颜色
		enum {
			BLACK = 0xff000000,
			RED = 0xffff0000,
			GREEN = 0xff00ff00,
			BLUE = 0xff0000ff,
			WHITE = 0xffffffff
		};
	public:
		//获取A,R,G,B值
		Byte& A() const noexcept{ return aColor; }
		Byte& R() const noexcept{ return rColor; }
		Byte& G() const noexcept{ return gColor; }
		Byte& B() const noexcept{ return bColor; }

		//获取A,R,G,B值的浮点型数据
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
			if (this == &cl)
				return *this;
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


	/// <summary>
	/// 笔刷
	/// 其实是像素数据，因为不仅是颜色，也可以是渐变颜色或纹理等形式，
	/// 目前没有使用渐变颜色，渐变色后期开发
	/// </summary>
	class Brush {
	public:
		Brush() noexcept;
		Brush(uint32_t color_v) noexcept;
		explicit Brush(const std::string& filePath) noexcept;
		~Brush() noexcept;
		Brush(const Brush& other) noexcept;
	public:
		//设置纹理路径
		void SetTexturePath(const std::string& filePath);
		Color& BColor() const noexcept{ return bColor; }
		std::string& TexturePath() const noexcept{ return texturePath; }
		bool HasTexture();
	public:
		Brush& operator=(const Brush& other) noexcept;
		Brush& operator=(const Color& color) noexcept;
	private:
		mutable Color bColor;
		mutable std::string texturePath;
	};
}
