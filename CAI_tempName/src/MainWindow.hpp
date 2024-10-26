#pragma once
#include "Shapes.h"
#include "log/Log.h"
#include <Events/Events.h>
using Brush = Draw::Brush;
class GG :public Grid {

protected:
	virtual void OnMouseOver(CAITF::MouseMoveEvent& e) override {
		std::cout << e.ToString() << std::endl;
		e.handled = true;
	}
};
class MainWindow : public Window
{
public:
	MainWindow(int width = 800, int height = 600) noexcept :Window(width, height) {
		CAITF::Log::init();
		initializeComponents();
		
		///���Դ���
		GG* grid = new GG();
		grid->setGridRCCollection(3, 3);
		grid->setBackground(Brush(Draw::Color::BLUE));
		setContent(*grid);
		Grid* grid2 = new Grid();
		grid2->setBackground(Brush(0xffff00ff));
		grid->setRC(grid2, 1, 1);
		Button* btn = new Button();
		btn->setWidth(500);
		btn->setHeight(20);
		btn->setZindex(12);
		//btn->setMargin(20,30,0,0);
		//btn->setContent(L"���");
		grid2->addChild(*btn);
		grid2->setBorderSize(10);
		grid2->setBorderBrush(Brush(0xff00fefe));
		btn->setBackground(Brush(Draw::Color::GREEN));
		grid->addChild(*grid2);
		LogNotice("system init finish{0}","--x");
		LogError("system error check,{1}", 10, "we");
	}
	~MainWindow() noexcept {
	}

private:
	void initializeComponents(void) {
		//��������ÿ�����ڶ�����һ������Ŀ���ǽ�����ӳ�䵽��׼�豸����
		name = "MainWindow";
	}

};
