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
	float width;	//����ʵ�ʴ�С //�����ȣ�����߶� ��λ������
	float height;
	float bearingX;//�ӻ�׼�ߵ�������/������ƫ��ֵ ��λ������
	float bearingY;
	unsigned int Advance;    // ԭ�����һ������ԭ��ľ��� ��СΪ 1/64����
};
/// <summary>
/// ������Ⱦ��Ϊʵʱ��Ԥ����ʵʱ�����ڹ̶����������£�����ui�Ϲ̶������֣�
/// ��Ԥ�����������������������ʱ�����������֮��ģ���ȻҲ��������ʵʱȻ��洢
/// ����Ч�����ܲ����룬ĳЩ�������ȴ�һ���ֿ���һ��
/// ��Ҫע����ǣ������в��õ��ַ�������unicode������ע���ⲿ�����ַ�����
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
	unsigned int fontSize; //����������С
	//Draw::Color fontColor;
private:
	FT_Library ft;
	FT_Face face;
	std::map<wchar_t, Character> characters;
	friend class PaintDevice;
	GLuint VAO;
	GLuint VBO;
};

