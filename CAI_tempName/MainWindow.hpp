#pragma once
#include"Window.h"
#include"Button.h"
#include "TedPanel.h"
static int w = 100;
static int h = 40;
class MainWindow : public Window
{
public:
	MainWindow() noexcept {

		/*TedPanel* P = new TedPanel();
		Button* bt1 = new Button();
		Button* bt2 = new Button();
		bt1->setHeight(30);
		bt1->setWidth(100);
		bt1->setBackground(Brush(0xff00ff00));
		bt2->setHeight(30);
		bt2->setWidth(100);
		bt2->setBackground(Brush(0xff00ff00));
		P->addChild(*bt1);
		P->addChild(*bt2);
		setContent(*P);*/
		initializeComponents();
		

	}
	~MainWindow() noexcept {
	}
private:
	void initializeComponents(void) {
		name = "MainWindow";
		setSize(1000,800 );
		float DPH = 1 / height.get()*2;
		float DPW = 1 / width.get()*2;

		//原点坐标平移矩阵
		Math::SquareMatrix<4> moveMatrix = {
			1,0,0,-width.get() / 2,
			0,1,0,-height.get() / 2,
			0,0,1,0,
			0,0,0,1
		};
		//长度映射矩阵
		Math::SquareMatrix<4> scalMatrix = {
			DPW,0,0,0,
			0,DPH,0,0,
			0,0,1,0,
			0,0,0,1
		};
		
		Size size(0,0,width.get(),height.get(),DPH,DPW);
		size.TransMatrix()=scalMatrix*moveMatrix;
		beginInit(size);
		int d = 10;
	}
	
};