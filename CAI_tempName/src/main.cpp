//Glad库用于获取Opengl函数指针以便使用Opengl函数
//glfw库则是用于创建窗口的
#include "caipch.h"
#include<chrono>
#include "MainWindow.hpp"
#include "UI/RenderEngine.h"


//帧率 实时计算法
void callFre() {
	static std::chrono::high_resolution_clock::time_point pre = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point nowTime = std::chrono::high_resolution_clock::now();
	int fp = static_cast<int>(1.f / (double)(nowTime - pre).count() * 1000 * 1000 * 1000);
	pre = nowTime;
}


int main() {
	
	if (CAIEngine.Initial())
		return -1;
	
	MainWindow mWindow(1000,800);
	mWindow.init();
	CAIEngine.AddRenderWindow(&mWindow);
	CAIEngine.Start();
	return 0;
}