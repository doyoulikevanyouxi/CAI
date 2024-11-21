#pragma once
#include "Object.h"
#include "Draw.h"
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

enum TextOverRangeOperator {
	Default,
	Wrap
};

struct FontSetting
{
	unsigned int size;
	Draw::Color color;
	TextOverRangeOperator operation;
};

struct Character
{
	GLuint textureID;
	float width;	//字体实际大小 //字体宽度，字体高度 单位：像素
	float height;
	float bearingX;//从基准线到字形左部/顶部的偏移值 单位：像素
	float bearingY;
	unsigned int Advance;    // 原点距下一个字形原点的距离 大小为 1/64像素
};
/// <summary>
/// 字体渲染分为实时和预处理，实时多用于固定不变的情况下，例如ui上固定的文字，
/// 而预处理则用于文字需求量大的时候，例如输入框之类的，当然也可以在先实时然后存储
/// 不过效果可能不理想，某些情况会出先打一个字卡顿一下
/// 需要注意的是：该类中采用的字符编码是unicode，所以注意外部传入字符编码
/// </summary>
class Font : public Object
{
public:
	Font() noexcept;
	~Font() noexcept;
public:
	void Load(const wchar_t& ch);
	void Load();
	Character& GetCharacter(unsigned int unicode) noexcept;
public:
	unsigned int fontSize; //字体期望大小
	//Draw::Color fontColor;
private:
	FT_Library ft;
	FT_Face face;
	std::map<wchar_t, Character> characters;
	friend class PaintDevice;
	GLuint VAO;
	GLuint VBO;
};

