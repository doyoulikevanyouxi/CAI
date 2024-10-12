//窗口类，继承至ContentControl
//只能设置Content属性，不能额外
//添加多个子控件
//在开发阶段，暂时移除了Window的
//循环，将所有的Window循环统一到
//一起，后期将会独立每个Window的
//循环
#pragma once
#include "ContentControl.h"
#include "Coordinate.h"
struct GLFWwindow;
class Window : public ContentControl
{
public:
	Window() noexcept;
	virtual ~Window() noexcept;
public:
	void activited();
	void show();
	GLFWwindow* getWinHD() noexcept;
public:
	void setSize(int width, int height) noexcept;
protected:
	GLFWwindow* winHd;
	Size size;
};

