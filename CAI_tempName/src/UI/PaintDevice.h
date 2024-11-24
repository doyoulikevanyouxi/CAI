#pragma once
class Size;
class ControlTemplate;
class Font;
struct FontSetting;
class Shader;

class PaintDevice 
{
	friend class RenderEngine;
public:
	PaintDevice() noexcept;
	~PaintDevice() noexcept;
public:
	void Init();
	void LoadShader();
public:
	void BindBufferData(ControlTemplate* style);
	void DrawString(const std::wstring& str,const Size& size,const FontSetting& fontSet) noexcept;
	void Draw(ControlTemplate* style) noexcept;
private:
	//��������
	unsigned int VAO;
	//���㻺�����
	unsigned int VBO;
	Font* font;
	Shader* fontShader;
	Shader* shader;
};

