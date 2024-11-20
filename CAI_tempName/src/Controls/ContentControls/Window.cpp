#include "caipch.h"
#include "Window.h"
#include "UI/RenderEngine.h"
#include "Datas/ControlStyle.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "UI/PaintDevice.h"
Window::Window() noexcept :winHd(NULL)
{
	if (CAIEngine.mainWHasToken) {
		winHd = CAIEngine.CreatWindow(400, 400, "TME");
	}
	else {
		this->winHd = CAIEngine.GetMainWindow();
		CAIEngine.mainWHasToken = true;
	}
	style->styleData().SetInvalid(true);
}

Window::Window(int width, int height) noexcept:Window()
{
	SetWidth(width);
	SetHeight(height);
}

Window::~Window() noexcept
{
}

void Window::activited()
{
	CAIEngine.ActivateWindow((GLFWwindow*)this->winHd);
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
	BeginInit(size);
	projection[2][2] =- 1.f / zmax;
	projection[3][2] = 1;
	CAIEngine.SetColorProjection(colorProjection);
	CAIEngine.SetWindowProjection(projection);

	
}

void Window::setSize(int width, int height) noexcept
{
	CAIEngine.SetWindowSize(winHd, width, height);
	SetHeight(height);
	SetWidth(width);
}

void Window::RenderLoop() noexcept
{
	glfwMakeContextCurrent(this->winHd);
	while (!glfwWindowShouldClose(this->winHd))
	{
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Render();
		glfwSwapBuffers(this->winHd);
		//glfwSwapBuffers(mainWinHd);
		glfwPollEvents();
	}
}


 