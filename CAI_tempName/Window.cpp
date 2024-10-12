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
	style->getData().setInvalid(true);
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

	//原点坐标平移矩阵
	Math::SquareMatrix<4> moveMatrix = {
		1,0,0,-width.get() / 2,
		0,1,0,-height.get() / 2,
		0,0,1,0,
		0,0,0,1
	};
	//长度映射矩阵
	Math::SquareMatrix<4> scalMatrix = {
		DPW,0,0,0,
		0,DPH,0,0,
		0,0,1,0,
		0,0,0,1
	};

	Size sizeT(0, 0, width.get(), height.get(), DPH, DPW);
	this->size = sizeT;
	size.TransMatrix() = scalMatrix * moveMatrix;
	beginInit(size);
}

void Window::setSize(int width, int height) noexcept
{
	CAIEngine.setWindowSize(winHd, width, height);
	setHeight(height);
	setWidth(width);
}


 