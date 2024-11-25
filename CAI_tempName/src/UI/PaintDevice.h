#pragma once
#include "Object.h"
#include "Datas/Coordinate.h"
#include "Datas/VisualData.h"
class Shader;
namespace Draw {
	class Brush;
}
struct FontSetting;
class Window;
using Brush = Draw::Brush;

class PaintDevice final : public Object
{
	friend class RenderEngine;
public:
	PaintDevice() noexcept;
	~PaintDevice() noexcept;
public:
	void UpdateData(const double* vertexData, const double* ColorData, const unsigned int* indexData);
	void UpdataVertex(const double* data);
	void UpdataColor(const double* data);
	void DrawText(const std::wstring& str, const Size& size, const FontSetting& fontSet) noexcept;
	void Draw(VisualData& data);
private:
	Shader* fontShader;
	Shader* rectShader;
	//顶点数组
	unsigned int VAO;
	//顶点缓冲对象
	unsigned int VBO;
	//索引缓冲对象
	unsigned int EBO;

};

