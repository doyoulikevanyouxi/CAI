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
	Window(int width, int height) noexcept;
	virtual ~Window() noexcept;
public:
	void activited();
	void show();
	GLFWwindow* getWinHD() noexcept;
	void init() noexcept;
public:
	void setSize(int width, int height) noexcept;
protected:
	//使用窗口本身的渲染循环，需要将循环放置到不同的线程中
	void renderLoop() noexcept;
protected:
	GLFWwindow* winHd;
	Size size;

};

