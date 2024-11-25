#include "caipch.h"
#include "PaintDevice.h"
#include <glad/glad.h>
#include "Draw.h"
#include "Character.h"
#include "RenderEngine.h"
#include "Shader.h"
#include "stbimge/stb_image.h"
#include "Application.h"

PaintDevice::PaintDevice() noexcept : fontShader(nullptr),rectShader(nullptr), VAO(0), VBO(0), EBO(0)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * 28, NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)(sizeof(double) * 12));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, NULL, GL_STATIC_DRAW);
	glBindVertexArray(0);
}



PaintDevice::~PaintDevice() noexcept
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void PaintDevice::UpdateData(const double* vertexData, const double* colorData,const unsigned int* indexData)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(double) * 12, vertexData);
	glBufferSubData(GL_ARRAY_BUFFER, 12*sizeof(double), sizeof(double) * 16, colorData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0, sizeof(unsigned int) * 6, indexData);
}

void PaintDevice::UpdataVertex(const double* data)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(double) * 12, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PaintDevice::UpdataColor(const double* data)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 12 * sizeof(double), sizeof(double) * 16, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/// <summary>
/// 绘制字符
/// </summary>
/// <param name="str">需要被绘制的字符</param>
/// <param name="size">允许绘制的区域</param>
/// <param name="fontSet">字体设置</param>
void PaintDevice::DrawText(const std::wstring& str, const Size& size,const FontSetting& fontSet) noexcept
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Font* ft = Application::app.renderEngine->GetFont();
	//缩放
	float scal = fontSet.size /(float)ft->fontSize;
	fontShader->Use();
	fontShader->SetMat4("model", size.TransMatrix());
	const Draw::Color& color = fontSet.color;
	fontShader->SetVec4("textColor", color.R_f(),color.G_f(),color.B_f(),255);
	glBindVertexArray(ft->VAO);
	float x = size.X();
	float xLeft = size.X() + size.Width();
	//为了将字符的基准线放置到同一水平面，需要固定高度，并将参照坐标移动至左下角
	float y = size.Y()+fontSet.size;
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
		float xpos = x + charac.bearingX*scal;
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
			xpos+w,ypos,size.Z(),1,0,
			xpos,ypos+h,size.Z(),0,1,

			xpos + w,ypos,size.Z(),1,0,
			xpos,ypos + h,size.Z(),0,1,
			xpos+w,ypos+h,size.Z(),1,1
		};
		
		x += (charac.Advance >>6 )*scal;
		glBindTexture(GL_TEXTURE_2D, charac.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, ft->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

void PaintDevice::Draw(VisualData& data)
{
	rectShader->Use();
	rectShader->SetMat4("model", data.AreaSize().TransMatrix());
	glBindVertexArray(VAO);

	if (data.hasBorder) {
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		glStencilMask(0xff);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		UpdataVertex(data.borderVertexData);
		UpdataColor(data.borderVertexColorData);
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		UpdataVertex(data.vertexData);
		UpdataColor(data.vertexColorData);
	}
	else {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

