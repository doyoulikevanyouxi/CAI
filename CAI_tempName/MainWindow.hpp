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
		//��������ÿ�����ڶ�����һ������Ŀ���ǽ�����ӳ�䵽��׼�豸����
		name = "MainWindow";
	}
	
};