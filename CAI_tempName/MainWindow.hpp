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
		/*Grid* grid = new Grid();
		setContent(*grid);
		grid->setBackground(Brush(Draw::Color::RED));*/
	/*	Grid* grid = new Grid();
		grid->addRowDefinition(RowDefinition());
		grid->addRowDefinition(RowDefinition());
		grid->addRowDefinition(RowDefinition());
		grid->addColumDefinition(ColumDefinition());
		grid->addColumDefinition(ColumDefinition());
		grid->addColumDefinition(ColumDefinition());
		grid->setBackground(Brush(0xFFF5F5F5));
		setContent(*grid);
		Grid* grid2 = new Grid();
		Grid* grid3 = new Grid();
		Grid* grid4 = new Grid();
		Grid* grid5 = new Grid();
		Grid* grid6 = new Grid();
		Grid* grid7 = new Grid();
		grid2->setBackground(Brush(0xffff0000));
		grid3->setBackground(Brush(0xff00ff00));
		grid4->setBackground(Brush(0xff0000ff));
		grid5->setBackground(Brush(0xffffff00));
		grid6->setBackground(Brush(0xff00ffff));
		grid7->setBackground(Brush(0xffff00ff));
		grid->addChild(*grid2);
		grid->addChild(*grid3);
		grid->addChild(*grid4);
		grid->addChild(*grid5);
		grid->addChild(*grid6);
		grid->addChild(*grid7);
		grid->setRC(grid2, 0, 0);
		grid->setRC(grid3, 0, 1);
		grid->setRC(grid4, 0, 2);
		grid->setRC(grid5, 1, 0);
		grid->setRC(grid6, 1, 1);
		grid->setRC(grid7, 1, 2);*/
	
	}
	~MainWindow() noexcept {
	}
private:
	void initializeComponents(void) {
		//以下设置每个窗口都会有一个，其目的是将坐标映射到标准设备坐标
		name = "MainWindow";
	}
	
};