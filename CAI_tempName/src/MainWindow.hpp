#pragma once
#include "Controls/Shapes.h"
#include "log/Log.h"
#include <Events/Events.h>
#include "UI/Application.h"
using Brush = Draw::Brush;
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
class MainWindow : public Window
{
public:
	MainWindow(int width = 800, int height = 600) noexcept :Window(width, height) {
		SetHeight(800);
		SetWidth(1000);
		Gridg* grid = new Gridg();
		grid->SetBackground(0xffffffff);
		grid->addColumDefinition(ColumDefinition());
		grid->addColumDefinition(ColumDefinition(400,true));
		grid->addRowDefinition(RowDefinition());
		grid->addRowDefinition(RowDefinition(300,true));
		TextBox* txtbox = new TextBox();
		txtbox->SetBorderSize(10);
		txtbox->SetBorderBrush(0xffffff00);
		txtbox->fontSize.set(20);
		txtbox->SetBackground(0xff0000ff);
		grid->setRC(txtbox, 0, 0);
		grid->setRowSpan(txtbox, 2);
		Gridg* gChild = new Gridg();
		gChild->SetBackground(0xffff0000);
		grid->setRC(gChild, 0, 1);
		TextBlock* tb = new TextBlock();
		tb->fontSize.set(20);
		tb->SetBackground(0xff00ff00);
		grid->setRC(tb, 1, 1);
		grid->AddChild(txtbox);
		//grid->AddChild(gChild);
		grid->AddChild(tb);
		tb->text.set(L"��ð�,\r\n��sb");
		setContent(grid);
		
		initializeComponents();

	}
	~MainWindow() noexcept {
	}
public:
	void Start() {
		Application::app.Start();
	}
private:
	void initializeComponents() {
		//��������ÿ�����ڶ�����һ������Ŀ���ǽ�����ӳ�䵽��׼�豸����
		name = CAISTR(MainWindow);
		Window::InitializeComponents();
	}
};
