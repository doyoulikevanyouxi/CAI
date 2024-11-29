#pragma once
#include "Object.h"
#include "Datas/Coordinate.h"
#include "Datas/VisualData.h"
namespace Draw {
	class Brush;
}
struct FontSetting;
class Geometry;
class LineGeometry;
class Shader;

class Window;
using Brush = Draw::Brush;

/// <summary>
/// 绘制设备句柄
/// 这是真正绘制图形的地方
/// 目前只提供文字和矩形的绘制，其他绘制需要等到glsl开发完毕后添加
/// </summary>
class PaintDevice final : public Object
{
	friend class RenderEngine;
public:
	PaintDevice() noexcept;
	~PaintDevice() noexcept;
public:
	//更新数据（所有数据，顶点，颜色，索引）
	void UpdateData(const double* vertexData, const double* ColorData, const unsigned int* indexData);
	//更新顶点数据
	void UpdataVertex(const double* data);
	//更新顶点颜色数据
	void UpdataColor(const double* data);
	//画线
	void DrawLine(const Size& size,const LineGeometry* data);
	//绘制文字
	void DrawText(const std::wstring& str, const Size& size, const FontSetting& fontSet) noexcept;
	//绘制元素
	void Draw(VisualData& data);
private:
	//绘制字体所需着色器，由RenderEngine提供
	Shader* fontShader;
	//绘制矩形所需着色器，由RenderEngine提供
	Shader* rectShader;
	Shader* geometryShader;
	//顶点数组
	unsigned int VAO;
	//顶点缓冲对象
	unsigned int VBO;
	//索引缓冲对象
	unsigned int EBO;
	unsigned int lineVAO;
	unsigned int lineVBO;

};

