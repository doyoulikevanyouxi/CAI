#include "caipch.h"
#include "Window.h"
#include "UI/Application.h"
#include "UI/RenderEngine.h"
#include "Datas/ControlStyle.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "UI/PaintDevice.h"
Window::Window() noexcept :winHd(NULL)
{
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

GLFWwindow* Window::getWinHD() noexcept
{
	return winHd;
}

void Window::SetSize(int width, int height) noexcept
{
	Application::app.renderEngine->SetWindowSize(winHd, width, height);
	SetHeight(height);
	SetWidth(width);
}

void Window::Init()
{
	UIElement::Init();
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

	Size sizeT(0, 0, 0, width.get(), height.get());
	sizeT.SetGlobalHeight(height.get());
	sizeT.SetGlobalWidth(width.get());
	this->size = sizeT;
	size.TransMatrix() = mt;
	CheckSize(size);
	projection[2][2] = -1.f / zmax;
	projection[3][2] = 1;
	Application::app.renderEngine->SetColorProjection(colorProjection);
	Application::app.renderEngine->SetWindowProjection(projection);
}

void Window::InitializeComponents()
{
	if (!initialConponentsDone) {
		initialConponentsDone = true;
	}
	if (!Application::app.Init()) {
		return;
	}
	winHd = Application::app.renderEngine->CreatWindow(width.get(), height.get(), this->name.c_str());
	if (winHd == nullptr) {
		return;
	}
	Application::app.renderEngine->AddRenderWindow(this);
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


 