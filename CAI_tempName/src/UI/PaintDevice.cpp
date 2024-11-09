#include "caipch.h"
#include "PaintDevice.h"
#include<glad/glad.h>
#include"Draw.h"
#include "Datas/ControlStyle.h"
#include "Character.h"
#include "RenderEngine.h"
#include "Shader.h"
#include "stbimge/stb_image.h"

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36, NULL, GL_STATIC_DRAW);
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

void PaintDevice::DrawText(const std::wstring& str, const Size& size,const FontSetting& fontSet) noexcept
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Font* ft = CAIEngine.getFont();
	//缩放
	float scal = fontSet.size /(float)ft->fontSize;

	CAIEngine.fontShader->use();
	CAIEngine.fontShader->setMat4("model", size.TransMatrix());
	const Draw::Color& color = fontSet.color;
	CAIEngine.fontShader->setVec4("textColor", color.R_f(),color.G_f(),color.B_f(),255);
	glBindVertexArray(ft->VAO);
	float x = size.X();
	//为了将字符的基准线放置到同一水平面，需要固定高度，并将参照坐标移动至左下角
	float y = size.Y()+fontSet.size;
	for (auto& chr : str) {
		
		auto& charac = ft->character(chr);

		float xpos = x + charac.bearingX*scal;
		//基准坐标向上移动
		float ypos = y-charac.bearingY*scal;
		float w = charac.width * scal;
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

void PaintDevice::Draw(ControlTemplate* style) noexcept
{
	const VisualData& data = style->vData;
	if (data.isInvalid())
		return;
	
	glBindVertexArray(VAO);
	//检查数据是否被送到了GPU处
	if (!style->vData.isDataHasBeenPushToGpu) {
		Brush* areaBrush = &(style->vData.AreaBrush());
		if (areaBrush->hasTexture()) {
			int width, height;
			int channel;
			Byte* data = stbi_load(areaBrush->TexturePath().c_str(), &width, &height, &channel, 0);
			if (data == NULL)
				std::cout << "can not load texture ,path:" << areaBrush->TexturePath().c_str() << std::endl;
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				data
			);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			style->vData.texture = texture;
			stbi_image_free(data);
		}
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 12, data.vertexData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 12,sizeof(float)*16, data.vertexColorData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 12+sizeof(float) * 16, sizeof(float) *8, data.textureIndexData);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.IndexSize(), data.VertexIndexData(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(12 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(28 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		style->vData.isDataHasBeenPushToGpu = true;
	}
	CAIEngine.squareShader->setMat4("model", data.AreaSize().TransMatrix());
	//检查是否存在边框，边框由模板测试实现，去除掉内容区域的绘制数据
	if (data.hasBorder) {
		//设置模板测试参数，允许该样式绘制的数据显示，并且将绘制区域模板数据设置为1
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		glStencilMask(0xff);
		//绘制样式
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 12, data.vertexData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 12, sizeof(float) * 16, data.vertexColorData);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//设置模板参数，边框区域实际上是内容区域的放大版
		//并且在模板数据非1处绘制
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*12, data.borderVertexData);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 12, sizeof(float)*16, data.borderVertexColorData);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//重置模板数据，使得后续所有绘制都通过，但是数据不写入模板中
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glStencilMask(0x00);
	}
	else {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

