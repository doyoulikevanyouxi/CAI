#pragma once
#include"Window.h"
#include"Button.h"
#include"ControlStyle.h"
class MainWindow : public Window
{
public:
	MainWindow() noexcept {
		Button* bt = new Button();
		setContent(*bt);
		bt->setHeight(200);
		bt->setWidth(300);
		bt->setBackground(Brush(0xff00ff00));
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
		measure(size);
		style->getData().setInvalid(true);
	}
	
};