#pragma once
#include"Window.h"
#include"Button.h"
#include "Grid.h"

class MainWindow : public Window
{
public:
	MainWindow(int width=800,int height=600) noexcept :Window(width, height) {
		initializeComponents();
		/*Grid* grid = new Grid();
		grid->setBackground(Brush(0xffffffff));
		setContent(*grid);*/
		Button* bt = new Button();
		bt->setWidthAndHeight(40, 40);
		bt->setBackground(Brush(0xffff0000));
		setContent(*bt);
		bt->setBackground(Brush("resources/icons/close.png"));
	/*	Grid* pGrid = new Grid();
		pGrid->setBackground(Brush(0xffffffff));
		pGrid->setGridRCCollection(2, 1);
		Grid* hGrid = new Grid();
		pGrid->setRC(hGrid, 0, 0);
		pGrid->addChild(*hGrid);*/
	}
	~MainWindow() noexcept {
	}
private:
	void initializeComponents(void) {
		//以下设置每个窗口都会有一个，其目的是将坐标映射到标准设备坐标
		name = "MainWindow";
	}

};
