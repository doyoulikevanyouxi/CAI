#pragma once
#include "Controls/Shapes.h"
#include "log/Log.h"
#include <Events/Events.h>
using Brush = Draw::Brush;
class Gridg : public Grid {

protected:
	void OnMouseEnter(MouseEnterEvent& e) override {
		std::cout << name << ": enter" << std::endl;
	}
	void OnMouseLeave(MouseLeaveEvent& e) override {
		std::cout << name << ": leave" << std::endl;
	}
};
class MainWindow : public Window
{
public:
	MainWindow(int width = 800, int height = 600) noexcept :Window(width, height) {
		initializeComponents();
		Gridg* grid = new Gridg();
		grid->name = "g1";
		grid->addColumDefinition(ColumDefinition());
		grid->addColumDefinition(ColumDefinition(400,true));
		grid->addRowDefinition(RowDefinition());
		grid->addRowDefinition(RowDefinition(300,true));
		TextBox* txtbox = new TextBox();
		txtbox->fontSize.set(20);
		txtbox->SetBackground(0xff0000ff);
		grid->setRC(txtbox, 0, 0);
		grid->setRowSpan(txtbox, 2);
		Gridg* gChild = new Gridg();
		gChild->name = "g2";
		gChild->SetBackground(0xffff0000);
		grid->setRC(gChild, 0, 1);
		TextBlock* tb = new TextBlock();
		tb->fontSize.set(20);
		tb->SetBackground(0xff00ff00);
		grid->setRC(tb, 1, 1);
		grid->AddChild(txtbox);
		grid->AddChild(gChild);
		grid->AddChild(tb);
		tb->text.set(L"safasf");
		setContent(grid);
	}
	~MainWindow() noexcept {
	}

private:
	void initializeComponents(void) {
		//以下设置每个窗口都会有一个，其目的是将坐标映射到标准设备坐标
		name = CAISTR(MainWindow);
	}
};
