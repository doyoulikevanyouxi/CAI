#include "caipch.h"
#include "PaintDevice.h"
#include<glad/glad.h>
#include "Datas/Coordinate.h"
#include "Datas/ControlStyle.h"
#include "Character.h"
#include "Shader.h"
#include "stbimge/stb_image.h"
#include "log/log.h"
#include "Application.h"

PaintDevice::PaintDevice() noexcept : VAO(0), VBO(0), font(nullptr), fontShader(nullptr), shader(nullptr)
{
}

PaintDevice::~PaintDevice() noexcept
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void PaintDevice::Init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void PaintDevice::LoadShader()
{

}

void PaintDevice::BindBufferData(ControlTemplate* style)
{
	VisualData& data = style->vData;
	if (data.IsInvalid())
		return;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3, data.originVertexData);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 3, sizeof(float) * 2, data.rectSizeData);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 5, sizeof(float)*4, data.colorData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

/// <summary>
/// �����ַ�
/// </summary>
/// <param name="str">��Ҫ�����Ƶ��ַ�</param>
/// <param name="size">������Ƶ�����</param>
/// <param name="fontSet">��������</param>
void PaintDevice::DrawString(const std::wstring& str, const Size& size, const FontSetting& fontSet) noexcept
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//����
	float scal = fontSet.size / (float)font->fontSize;

	fontShader->Use();
	fontShader->SetMat4("model", size.TransMatrix());
	const Draw::Color& color = fontSet.color;
	fontShader->SetVec4("textColor", color.R_f(), color.G_f(), color.B_f(), 255);
	glBindVertexArray(font->VAO);
	float x = size.X();
	float xLeft = size.X() + size.Width();
	//Ϊ�˽��ַ��Ļ�׼�߷��õ�ͬһˮƽ�棬��Ҫ�̶��߶ȣ��������������ƶ������½�
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

		auto& charac = font->GetCharacter(chr);
		float xpos = x + charac.bearingX * scal;
		//��׼���������ƶ�
		float w = charac.width * scal;
		//����ַ������˿ɻ�������
		//��ô�ͻ��в���x����Ϊ��ʼֵ
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
		glBindBuffer(GL_ARRAY_BUFFER, font->VBO);
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
	glDisable(GL_BLEND);
}


void PaintDevice::Draw(ControlTemplate* style) noexcept
{
	VisualData& data = style->vData;
	if (data.IsInvalid())
		return;
	shader->Use();
	glBindVertexArray(VAO);
	//���øÿؼ���ģ�;���
	shader->SetMat4("model", data.AreaSize().TransMatrix());
	if (data.hasBorder) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glClearStencil(0);
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		glStencilMask(0xff);
		glDrawArrays(GL_POINTS, 0, 1);
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);
		//���Ʊ߿�
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3, data.bordderVertexData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 3, sizeof(float) * 2, data.borderRectSizeData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 5, sizeof(float) * 4, data.borderColorData);
		glDrawArrays(GL_POINTS, 0, 1);
		//��buffer���ݻָ�
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3, data.originVertexData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 3, sizeof(float) * 2, data.rectSizeData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 5, sizeof(float) * 4, data.colorData);
		glStencilFunc(GL_ALWAYS, 0, 0xff);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glBindVertexArray(0);
}

