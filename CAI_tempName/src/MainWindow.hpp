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
		
		/*Line* line = new Line();
		line->SetPoint(100, 100, 200, 200);
		setContent(line);*/
	
		
		Gridg* grid = new Gridg();
		grid->SetBackground(0xffffff00);
		grid->addColumDefinition(ColumDefinition());
		grid->addColumDefinition(ColumDefinition(400,true));
		grid->addRowDefinition(RowDefinition());
		grid->addRowDefinition(RowDefinition(300,true));
		TextBox* txtbox = new TextBox();
		/*BoolAnimation* animate = new BoolAnimation();
		animate->From = true;
		animate->To = false;
		animate->Target = txtbox->GetVisible();
		animate->Repeat = true;
		animate->duration.timeSpan = 1.0;
		animate->delayDuration.timeSpan = 1.0;
		txtbox->storybord.AddAnimation(animate);
		txtbox->BeginAnimation();*/
		txtbox->SetBorderSize(10);
		txtbox->SetBorderBrush(0xffff00ff);
		txtbox->fontSize.set(20);
		txtbox->SetBackground(0xff0000ff);
		grid->setRC(txtbox, 0, 0);
		grid->setRowSpan(txtbox, 2);
		Gridg* gChild = new Gridg();
		gChild->SetBackground(0xffff0000);
		grid->setRC(gChild, 0, 1);
		TextBlock* tb = new TextBlock();
		tb->SetRadius(20);
		tb->fontSize.set(20);
		tb->SetBackground(0xff00ff00);
		grid->setRC(tb, 1, 1);
		grid->AddChild(txtbox);
		grid->AddChild(gChild);
		grid->AddChild(tb);
		//tb->text.set(L"你好啊,\r\n大sb");
		setContent(grid);
	}
	~MainWindow() noexcept {
	}

private:
	void InitializeComponent(void) {
		Application::app.Init();
		name = CAISTR(MainWindow);
	}
};
