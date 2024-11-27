#pragma once
#include "Object.h"
#include "Draw.h"
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
//字体超出渲染范围的操作
enum TextOverRangeOperator {
	//默认，不做任何操作
	Default,
	//换行
	Wrap
};

/// <summary>
/// 字体设置
/// </summary>
struct FontSetting
{
	//字体大小
	unsigned int size;
	//字体颜色
	Draw::Color color;
	//超出部分的操作
	TextOverRangeOperator operation;
};

/// <summary>
/// 字符相关数据
/// </summary>
struct Character
{
	//字符加载时的纹理ID
	GLuint textureID;
	float width;	//字体实际宽度 //字体宽度，字体高度 单位：像素
	float height;//字体实际高度 
	float bearingX;//从基准线到字形左部 单位：像素
	float bearingY;//从基准线到顶部的偏移值 
	unsigned int Advance;    // 原点距下一个字形原点的距离 大小为 1/64像素
};
/// <summary>
/// 字体库
/// 该类会根据字体库文件和符号的unicode值获取纹理
/// </summary>
class Font : public Object
{
public:
	Font() noexcept;
	~Font() noexcept;
public:
	//加载单个字符纹理
	//参数为字符的unicode，由于单字节和多字节的unicode字节不一样，所以统一用宽字符存储
	void Load(const wchar_t& ch);
	//加载所有字符
	//不建议使用，因为字体库本身字符就很多，加载慢，且耗费极大的内存空概念
	void Load();
	//获取字符
	Character& GetCharacter(unsigned int unicode) noexcept;
public:
	unsigned int fontSize; //字体期望大小
private:
	//freetype库用，ft表示类似于字体库文件
	FT_Library ft;
	//当前字符的相关属性，参照Character，但是没有纹理ID
	FT_Face face;
	//存储已加载的字符
	std::map<wchar_t, Character> characters;
	friend class PaintDevice;
	//字符专用Opengl的buffer
	GLuint VAO;
	GLuint VBO;
};

