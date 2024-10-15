#pragma once
#include"Window.h"
#include"Button.h"
#include "Grid.h"
static int w = 100;
static int h = 40;
class MainWindow : public Window
{
public:
	MainWindow(int width=800,int height=600) noexcept :Window(width, height) {
		initializeComponents();
	}
	~MainWindow() noexcept {
	}
private:
	void initializeComponents(void) {
		//以下设置每个窗口都会有一个，其目的是将坐标映射到标准设备坐标
		name = "MainWindow";
	}
	
};