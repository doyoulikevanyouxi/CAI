#pragma once
#include "Controls/Shapes.h"
#include "log/Log.h"
#include <Events/Events.h>
using Brush = Draw::Brush;
class GG :public Grid {

protected:
	virtual void OnMouseOver(CAITF::MouseMoveEvent& e) override {
	//	std::cout << e.ToString() << std::endl;
		e.handled = true;
	}
};
class MainWindow : public Window
{
public:
	MainWindow(int width = 800, int height = 600) noexcept :Window(width, height) {
		initializeComponents();
		///���Դ���
		GG* grid = new GG();
		
		grid->setGridRCCollection(3, 3);
		//grid->setBackground(Brush(Draw::Color::BLUE));
		setContent(*grid);
		/*TextBlock* tx = new TextBlock();
		grid->addChild(*tx);
		tx->setText(L"asfNi���");*/
		TextBox* tx = new TextBox();

		grid->addChild(*tx);
		grid->setRC(tx, 1, 1);
	
	}
	~MainWindow() noexcept {
	}

private:
	void initializeComponents(void) {
		//��������ÿ�����ڶ�����һ������Ŀ���ǽ�����ӳ�䵽��׼�豸����
		name = CAISTR(MainWindow);
	}
};
