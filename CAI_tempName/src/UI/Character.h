#pragma once
#include "Object.h"
#include "Draw.h"
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
//���峬����Ⱦ��Χ�Ĳ���
enum TextOverRangeOperator {
	//Ĭ�ϣ������κβ���
	Default,
	//����
	Wrap
};

/// <summary>
/// ��������
/// </summary>
struct FontSetting
{
	//�����С
	unsigned int size;
	//������ɫ
	Draw::Color color;
	//�������ֵĲ���
	TextOverRangeOperator operation;
};

/// <summary>
/// �ַ��������
/// </summary>
struct Character
{
	//�ַ�����ʱ������ID
	GLuint textureID;
	float width;	//����ʵ�ʿ�� //�����ȣ�����߶� ��λ������
	float height;//����ʵ�ʸ߶� 
	float bearingX;//�ӻ�׼�ߵ������� ��λ������
	float bearingY;//�ӻ�׼�ߵ�������ƫ��ֵ 
	unsigned int Advance;    // ԭ�����һ������ԭ��ľ��� ��СΪ 1/64����
};
/// <summary>
/// �����
/// ��������������ļ��ͷ��ŵ�unicodeֵ��ȡ����
/// </summary>
class Font : public Object
{
public:
	Font() noexcept;
	~Font() noexcept;
public:
	//���ص����ַ�����
	//����Ϊ�ַ���unicode�����ڵ��ֽںͶ��ֽڵ�unicode�ֽڲ�һ��������ͳһ�ÿ��ַ��洢
	void Load(const wchar_t& ch);
	//���������ַ�
	//������ʹ�ã���Ϊ����Ȿ���ַ��ͺܶ࣬���������ҺķѼ�����ڴ�ո���
	void Load();
	//��ȡ�ַ�
	Character& GetCharacter(unsigned int unicode) noexcept;
public:
	unsigned int fontSize; //����������С
private:
	//freetype���ã�ft��ʾ������������ļ�
	FT_Library ft;
	//��ǰ�ַ���������ԣ�����Character������û������ID
	FT_Face face;
	//�洢�Ѽ��ص��ַ�
	std::map<wchar_t, Character> characters;
	friend class PaintDevice;
	//�ַ�ר��Opengl��buffer
	GLuint VAO;
	GLuint VBO;
};

