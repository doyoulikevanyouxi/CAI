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
/// �����豸���
/// ������������ͼ�εĵط�
/// Ŀǰֻ�ṩ���ֺ;��εĻ��ƣ�����������Ҫ�ȵ�glsl������Ϻ����
/// </summary>
class PaintDevice final : public Object
{
	friend class RenderEngine;
public:
	PaintDevice() noexcept;
	~PaintDevice() noexcept;
public:
	//�������ݣ��������ݣ����㣬��ɫ��������
	void UpdateData(const float* vertexData, const float* size, const float* color, const float* radius, const float* borderSize, const float* borderColor);
	//���¶�������
	void UpdateVertex(const float* data);
	//���¾��δ�С
	void UpdateSize(const float* size);

	//���¶�����ɫ����
	void UpdateColor(const float* data);
	//���½ǰ뾶
	void UpdateRadius(const float* data);
	//���±߿��С
	void UpdateBorderSize(const float* data);
	//���±߿���ɫ
	void UpdateBoderColor(const float* data);
	//����
	void DrawLine(const Size& size,const LineGeometry* data);
	//��������
	void DrawText(const std::wstring& str, const Size& size, const FontSetting& fontSet) noexcept;
	//����Ԫ��
	void Draw(VisualData& data);
private:
	//��������������ɫ������RenderEngine�ṩ
	Shader* fontShader;
	//���ƾ���������ɫ������RenderEngine�ṩ
	Shader* rectShader;
	Shader* geometryShader;
	//��������
	unsigned int VAO;
	//���㻺�����
	unsigned int VBO;
	
	unsigned int lineVAO;
	unsigned int lineVBO;

};

