#include "caipch.h"
#include "Window.h"
#include "UI/RenderEngine.h"
#include "UI/Application.h"
Window::Window() noexcept :winHd(nullptr)
{
}

Window::Window(int width, int height) noexcept:Window()
{
	SetWidth(width);
	SetHeight(height);
}

Window::~Window() noexcept
{
}


bool Window::Init()
{
	//��ȡ����
	winHd = Application::app.renderEngine->GLCreateWindow(width.get(),height.get(),name.c_str());
	if (winHd == nullptr)
		return false;
	Visual::Init();
	Application::app.renderEngine->AddRenderWindow(this);
	float DPH = 1 / height.get() * 2;
	float DPW = 1 / width.get() * 2;
	//ͶӰ����
	Math::SquareMatrix<4> projection = {
		DPW,0,0,0,
		0,-DPH,0,0,
		0,0,1,0,
		-1,1,0,1
	};
	//��ɫͶӰ����
	float colorProjection[] = {
		1.f / 255,0,0,0,
		0,1.f / 255,0,0,
		0,0,1.f / 255,0,
		0,0,0,1.f / 255
	};
	//ģ�;���
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
	Application::app.renderEngine->SetResolution(width.get(),height.get());
	return true;
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