#include "PaintDevice.h"
#include<glad/glad.h>
#include"Draw.h"
#include "ControlStyle.h"
#include "Character.h"
#include "RenderEngine.h"
#include "Shader.h"
#include <iostream>
PaintDevice::PaintDevice() noexcept : pen(new Draw::Brush(Draw::Color::BLACK)),fill(new Draw::Brush(Draw::Color::BLACK)), hd(nullptr), VAO(0), VBO(0), EBO(0), areadySet(false)
{
}

PaintDevice::PaintDevice(Window* wnd) noexcept : PaintDevice()
{
	setWindow(wnd);
}

PaintDevice::~PaintDevice() noexcept
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void PaintDevice::setWindow(Window* wnd) noexcept
{
	if (areadySet)
		return;
	hd = wnd;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(0);
	areadySet = true;
}

void PaintDevice::setPen(const Brush& pen) noexcept
{
	*(this->pen) = pen;
}

void PaintDevice::fillWith(Brush& bs) noexcept
{
}

void PaintDevice::DrawText(const std::wstring& str, const Size& size) noexcept
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Font* ft = CAIEngine.getFont();
	unsigned int fontSize = ft->fontSize;
	CAIEngine.fontShader->use();
	CAIEngine.fontShader->setMat4("model", size.TransMatrix());
	CAIEngine.fontShader->setVec3("textColor", 1.0, 0.0, 0.0);
	glBindVertexArray(ft->VAO);
	float x = size.X();
	float y = size.Y()+fontSize;
	for (auto& chr : str) {
		
		auto& charac = ft->character(chr);
		float xpos = x + charac.bearingX;
		float ypos = y-charac.bearingY;
		float vertices[6][4] = {
			{xpos,ypos,0,0},
			{xpos+charac.width,ypos,1,0},
			{xpos,ypos+charac.height,0,1},

			{xpos + charac.width,ypos,1,0},
			{xpos,ypos + charac.height,0,1},
			{xpos+charac.width,ypos+charac.height,1,1}
		};
		x += (charac.Advance >>6 );
		glBindTexture(GL_TEXTURE_2D, charac.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, ft->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PaintDevice::DrawLine(const Point& initial, Point& end) noexcept
{
	glBindVertexArray(VAO);
}

void PaintDevice::DrawLines(const Point points[], size_t lineNum) noexcept
{
}

void PaintDevice::DrawRect(const Point& initial, float width, float height) noexcept
{
	float rC = pen->BColor().R();
	float gC = pen->BColor().G();
	float bC = pen->BColor().B();

	float data[] = {
		initial.X(),initial.Y(),1.0f,rC,gC,bC,
		initial.X()+width,initial.Y(),1.0f,rC,gC,bC,
		initial.X(),initial.Y()-height,1.0f,rC,gC,bC,
		initial.X()+width,initial.Y()-height,1.0f,rC,gC,bC,
	};
	unsigned int dataIndex[] = {
		0,1,2,
		1,2,3
	};

	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dataIndex), dataIndex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

volatile void PaintDevice::Draw(ControlStyle* style) noexcept
{
	const VisualData& data = style->vData;
	if (data.isInvalid())
		return;
	CAIEngine.squareShader->setMat4("model", data.AreaSize().TransMatrix());
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* data.VertexSize(), data.VertexData(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.IndexSize(), data.VertexIndexData(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
