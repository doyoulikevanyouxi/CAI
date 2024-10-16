#include "Window.h"
#include "RenderEngine.h"
#include "ControlStyle.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "PaintDevice.h"
#include <iostream>
Window::Window() noexcept :winHd(NULL)
{
	if (CAIEngine.mainWHasToken) {
		winHd = CAIEngine.creatWindow(400, 400, "TME");
	}
	else {
		this->winHd = CAIEngine.getMainWindow();
		CAIEngine.mainWHasToken = true;
	}
	style->styleData().setInvalid(true);
}

Window::Window(int width, int height) noexcept:Window()
{
	setWidth(width);
	setHeight(height);
}

Window::~Window() noexcept
{
}

void Window::activited()
{
	CAIEngine.activateWindow((GLFWwindow*)this->winHd);
}

GLFWwindow* Window::getWinHD() noexcept
{
	return winHd;
}

void Window::init() noexcept
{
	setSize(width.get(),height.get() );
	float DPH = 1 / height.get() * 2;
	float DPW = 1 / width.get() * 2;
	//投影矩阵
	Math::SquareMatrix<4> projection = {
		DPW,0,0,0,
		0,-DPH,0,0,
		0,0,1,0,
		-1,1,0,1
	};
	//颜色投影矩阵
	float colorProjection[] = {
		1.f / 255,0,0,0,
		0,1.f / 255,0,0,
		0,0,1.f / 255,0,
		0,0,0,1.f / 255
	};
	//模型矩阵
	Math::TransMatrix mt = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	
	Size sizeT(0, 0,0, width.get(), height.get());
	this->size = sizeT;
	size.TransMatrix() = mt;
	beginInit(size);
	projection[2][2] =- 1.f / zmax;
	projection[3][2] = 1;
	CAIEngine.setColorProjection(colorProjection);
	CAIEngine.setWindowProjection(projection);

	
}

void Window::setSize(int width, int height) noexcept
{
	CAIEngine.setWindowSize(winHd, width, height);
	setHeight(height);
	setWidth(width);
}

void Window::renderLoop() noexcept
{
	glfwMakeContextCurrent(this->winHd);
	while (!glfwWindowShouldClose(this->winHd))
	{
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render();
		glfwSwapBuffers(this->winHd);
		//glfwSwapBuffers(mainWinHd);
		glfwPollEvents();
	}
}


 