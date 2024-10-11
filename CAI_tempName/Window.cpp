#include "Window.h"
#include "RenderEngine.h"
#include "ControlStyle.h"
Window::Window() noexcept :winHd(NULL)
{
	if (CAIEngine.mainWHasToken) {
		winHd = CAIEngine.creatWindow(400, 400, "TME");
	}
	else {
		this->winHd = CAIEngine.getMainWindow();
		CAIEngine.mainWHasToken = true;
	}
	size.TransMatrix() = {
		1,0,0,-width.get(),
		0,1,0,-height.get(),
		0,0,1,0,
		0,0,0,1
	};
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

void Window::setSize(int width, int height) noexcept
{
	CAIEngine.setWindowSize(winHd, width, height);
	this->height = height;
	this->width = width;
}


 