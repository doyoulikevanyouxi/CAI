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
		///测试代码
		GG* grid = new GG();
		grid->setGridRCCollection(3, 3);
		grid->SetBackground(Brush(Draw::Color::BLUE));
		setContent(*grid);
		TextBox* tx = new TextBox();
		tx->fontBrush.set(Draw::Color(Draw::Color::GREEN));
		tx->fontSize.set(20);
		tx->SetBackground(0xffccefda);
		grid->addChild(*tx);
		grid->setRC(tx, 1, 1);
	
	}
	~MainWindow() noexcept {
	}

private:
	void initializeComponents(void) {
		//以下设置每个窗口都会有一个，其目的是将坐标映射到标准设备坐标
		name = CAISTR(MainWindow);
	}
};
