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
	Pair<float> size;	//����ʵ�ʴ�С
	Pair<float> bearing; //�ӻ�׼�ߵ�������/������ƫ��ֵ
	unsigned int     Advance;    // ԭ�����һ������ԭ��ľ���
};
/// <summary>
/// ������Ⱦ��Ϊʵʱ��Ԥ����ʵʱ�����ڹ̶����������£�����ui�Ϲ̶������֣�
/// ��Ԥ�����������������������ʱ�����������֮��ģ���ȻҲ��������ʵʱȻ��洢
/// ����Ч�����ܲ����룬ĳЩ�������ȴ�һ���ֿ���һ��
/// </summary>
class Font : public Object
{
public:
	Font() noexcept;
	~Font() noexcept;
public:
	void Load(const wchar_t * ch);
public:
	unsigned int fontSize; //����������С
private:
	FT_Library ft;
	FT_Face face;
	std::map<wchar_t, Character> characters;
	GLuint VAO;
	GLuint VBO;
	GLuint texture;
};

