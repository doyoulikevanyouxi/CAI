//窗口类，继承至ContentControl
//只能设置Content属性，不能额外
//添加多个子控件
//在开发阶段，暂时移除了Window的
//循环，将所有的Window循环统一到
//一起，后期将会独立每个Window的
//循环
#pragma once
#include "../ContentControl.h"
#include "Datas/Coordinate.h"
struct GLFWwindow;
class Window : public ContentControl
{
public:
	Window() noexcept;
	Window(int width, int height) noexcept;
	virtual ~Window() noexcept;
public:
	GLFWwindow* getWinHD() noexcept;
public:
	void SetSize(int width, int height) noexcept;
	void Init();
protected:
	virtual void InitializeComponents();
	//使用窗口本身的渲染循环，需要将循环放置到不同的线程中
	void RenderLoop() noexcept;

protected:
	GLFWwindow* winHd;
	Size size;
private:
	bool initialConponentsDone = false;
};

