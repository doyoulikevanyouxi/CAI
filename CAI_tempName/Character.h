#pragma once
#include "Object.h"
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include<string>
#include<map>
template<class _T>
struct Pair
{
	_T first;
	_T second;
};
struct Character
{
	GLuint textureID;
	Pair<float> size;	//字体实际大小
	Pair<float> bearing; //从基准线到字形左部/顶部的偏移值
	unsigned int     Advance;    // 原点距下一个字形原点的距离
};
/// <summary>
/// 字体渲染分为实时和预处理，实时多用于固定不变的情况下，例如ui上固定的文字，
/// 而预处理则用于文字需求量大的时候，例如输入框之类的，当然也可以在先实时然后存储
/// 不过效果可能不理想，某些情况会出先打一个字卡顿一下
/// </summary>
class Font : public Object
{
public:
	Font() noexcept;
	~Font() noexcept;
public:
	void Load(const wchar_t * ch);
public:
	unsigned int fontSize; //字体期望大小
private:
	FT_Library ft;
	FT_Face face;
	std::map<wchar_t, Character> characters;
	GLuint VAO;
	GLuint VBO;
	GLuint texture;
};

