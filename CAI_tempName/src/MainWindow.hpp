#pragma once
#include "Controls/Shapes.h"
#include "log/Log.h"
#include <Events/Events.h>
#include <UI/Application.h>
#include <Animation/BoolAnimation.h>
using Brush = Draw::Brush;
//用于测试鼠标事件用
class Gridg : public Grid {
	
protected:
	//Draw::Color color;
	/*void OnMouseEnter(MouseEnterEvent& e) override {
		std::cout << name << ": enter" << std::endl;
	}
	void OnMouseLeave(MouseLeaveEvent& e) override {
		std::cout << name << ": leave" << std::endl;
	}*/

};
/// <summary>
/// 主窗口，也是程序的入口点
/// </summary>
class MainWindow : public Window
{
public:
	MainWindow(int width = 800, int height = 600) noexcept :Window(width, height) {
		InitializeComponent();
		

		/*Gridg* grid = new Gridg();
		grid->SetBackground(0xffffffff);
		grid->addColumDefinition(ColumDefinition());
		grid->addColumDefinition(ColumDefinition(400,true));
		grid->addRowDefinition(RowDefinition());
		grid->addRowDefinition(RowDefinition(300,true));*/
		TextBox* txtbox = new TextBox();

		txtbox->SetBorderSize(10);
		txtbox->SetBorderBrush(0xffff00ff);
		txtbox->SetFontSize(20);
		txtbox->SetBackground(0xff0000ff);
		/*grid->setRC(txtbox, 0, 0);
		grid->setRowSpan(txtbox, 2);
		grid->AddChild(txtbox);*/
		setContent(txtbox);
	}
	~MainWindow() noexcept {
	}

private:
	void InitializeComponent(void) {
		Application::app.Init();
		name = CAISTR(MainWindow);
	}
};
