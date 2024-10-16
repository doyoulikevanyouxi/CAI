#pragma once
#include"Window.h"
#include"Button.h"
#include "Grid.h"

class MainWindow : public Window
{
public:
	MainWindow(int width=800,int height=600) noexcept :Window(width, height) {
		initializeComponents();

		///���Դ���
		Grid* grid = new Grid();
		grid->setGridRCCollection(3, 3);
		grid->setBackground(Brush(Draw::Color::BLUE));
		setContent(*grid);
		Grid* grid2 = new Grid();
		grid2->setBackground(Brush(0xffff00ff));
		grid->setRC(grid2, 1, 0);
		Button* btn = new Button();
		btn->setWidth(100);
		btn->setHeight(20);
		btn->setZindex(12);
		//btn->setContent(L"���");
		grid2->addChild(*btn);
		btn->setBackground(Brush(Draw::Color::GREEN));
		grid->addChild(*grid2);
		///
	}
	~MainWindow() noexcept {
	}
private:
	void initializeComponents(void) {
		//��������ÿ�����ڶ�����һ������Ŀ���ǽ�����ӳ�䵽��׼�豸����
		name = "MainWindow";
	}

};
