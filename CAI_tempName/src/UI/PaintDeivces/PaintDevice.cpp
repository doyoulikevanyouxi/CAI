#include "caipch.h"
#include "PaintDevice.h"
#include <glad/glad.h>
#include "UI/Draw.h"
#include "UI/Character.h"
#include "UI/RenderEngine.h"
#include "UI/Shader.h"
#include "stbimge/stb_image.h"
#include "UI/Application.h"
#include "Datas/Geometry/LineGeometry.h"

PaintDevice::PaintDevice() noexcept : fontShader(nullptr), rectShader(nullptr), geometryShader(nullptr), VAO(0), VBO(0), lineVAO(0), lineVBO(0)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, NULL, GL_STATIC_DRAW);
	//顶点
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//大小
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	//颜色
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);
	//半径
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 9));
	glEnableVertexAttribArray(3);
	//边框大小
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(float), (void*)(sizeof(float) * 13));
	glEnableVertexAttribArray(4);
	//边框颜色
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 14));
	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//画线用的buffer--暂时
	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);
	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 14, NULL, GL_STATIC_DRAW);
	//顶点
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * 9));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * 11));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(float), (void*)(sizeof(float) * 13));
	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



PaintDevice::~PaintDevice() noexcept
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteVertexArrays(1, &lineVAO);
	glDeleteBuffers(1, &lineVBO);
}

void PaintDevice::UpdateData(const float* vertexData, const float* size, const float* color, const float* radius, const float* borderSize, const float* borderColor)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float), vertexData);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), 2 * sizeof(float), size);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * sizeof(float), 4 * sizeof(float), color);
	glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(float), 4 * sizeof(float), radius);
	glBufferSubData(GL_ARRAY_BUFFER, 13 * sizeof(float), 1 * sizeof(float), borderSize);
	glBufferSubData(GL_ARRAY_BUFFER, 14 * sizeof(float), 4 * sizeof(float), borderColor);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PaintDevice::UpdateVertex(const float* data)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PaintDevice::UpdateSize(const float* size)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), sizeof(float) * 2, size);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PaintDevice::UpdateColor(const float* data)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * sizeof(float), sizeof(float) * 4, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PaintDevice::UpdateRadius(const float* data)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(float), sizeof(float) * 4, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PaintDevice::UpdateBorderSize(const float* data)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 13 * sizeof(float), sizeof(float), data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PaintDevice::UpdateBoderColor(const float* data)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 14 * sizeof(float), sizeof(float) * 4, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PaintDevice::DrawLine(const VisualData& data, const LineGeometry& lineData,float lineThickness)
{
	if (!data.Visuble())
		return;
	float line1[] = {
		lineData.StartPoint().X(),
		lineData.StartPoint().Y()
	};
	float line2[] = {
		lineData.EndPoint().X(),
		lineData.EndPoint().Y()
	};
	geometryShader->Use();
	geometryShader->SetMat4("model", data.AreaSize().ModelMatrix());
	geometryShader->SetVec2("iResolution", data.AreaSize().ResolutionWidth(), data.AreaSize().ResolutionHeight());

	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3, data.VertexData());
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), 2 * sizeof(float), data.SizeData());
	glBufferSubData(GL_ARRAY_BUFFER, 5 * sizeof(float), 4 * sizeof(float), data.VertexColorData());
	glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(float), 2 * sizeof(float), line1);
	glBufferSubData(GL_ARRAY_BUFFER, 11 * sizeof(float), 2 * sizeof(float), line2);
	glBufferSubData(GL_ARRAY_BUFFER, 13 * sizeof(float), 1 * sizeof(float), &lineThickness);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

/// <summary>
/// 绘制字符
/// </summary>
/// <param name="str">需要被绘制的字符</param>
/// <param name="size">允许绘制的区域</param>
/// <param name="fontSet">字体设置</param>
void PaintDevice::DrawText(const std::wstring& str, const Size& size, const FontSetting& fontSet) noexcept
{
	Point pt(size.X(), size.Y());
	Point::TranslatTo(pt, size.ModelMatrix());
	Point::Reverse(pt, size.ResolutionHeight());
	Point::SetToLeftBottom(pt, size.Height());
	glScissor(pt.X(), pt.Y(), size.Width(), size.Height());
	Font* ft = Application::app.renderEngine->GetFont();
	//缩放
	float scal = fontSet.size / (float)ft->fontSize;
	fontShader->Use();
	fontShader->SetMat4("model", size.ModelMatrix());
	const Draw::Color& color = fontSet.color;
	fontShader->SetVec4("textColor", color.R_f(), color.G_f(), color.B_f(), 255);
	glBindVertexArray(ft->VAO);
	float x = size.X();
	float xLeft = size.X() + size.Width();
	//为了将字符的基准线放置到同一水平面，需要固定高度，并将参照坐标移动至左下角
	float y = size.Y() + fontSet.size;
	for (auto& chr : str) {
		if (chr == L'\r') {
			x = size.X();
			continue;
		}
		if (chr == L'\n') {
			y += fontSet.size;
			continue;
		}

		auto& charac = ft->GetCharacter(chr);
		float xpos = x + charac.bearingX * scal;
		//基准坐标向上移动
		float w = charac.width * scal;
		//如果字符超出了可绘制区域
		//那么就换行并且x重置为初始值
		if (fontSet.operation == TextOverRangeOperator::Wrap) {
			if (xpos + w > xLeft) {
				y += fontSet.size;
				x = size.X();
				xpos = x + charac.bearingX * scal;
			}
		}
		float ypos = y - charac.bearingY * scal;
		float h = charac.height * scal;
		float vertices[] = {
			xpos,ypos,size.Z(), 0,0,
			xpos + w,ypos,size.Z(),1,0,
			xpos,ypos + h,size.Z(),0,1,

			xpos + w,ypos,size.Z(),1,0,
			xpos,ypos + h,size.Z(),0,1,
			xpos + w,ypos + h,size.Z(),1,1
		};

		x += (charac.Advance >> 6) * scal;
		glBindTexture(GL_TEXTURE_2D, charac.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, ft->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PaintDevice::Draw(VisualData& data)
{
	if (!data.Visible())
		return;
	rectShader->Use();
	//rectShader->SetMat4("projection", data.AreaSize().ProjectionMatrix());
	rectShader->SetMat4("model", data.AreaSize().ModelMatrix());
	rectShader->SetVec2("iResolution", data.AreaSize().ResolutionWidth(), data.AreaSize().ResolutionHeight());
	glBindVertexArray(VAO);
	glScissor(data.ClipSize().X(), data.ClipSize().Y(), data.ClipSize().Width(), data.ClipSize().Height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

