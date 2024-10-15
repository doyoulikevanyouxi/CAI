//Glad�����ڻ�ȡOpengl����ָ���Ա�ʹ��Opengl����
//glfw���������ڴ������ڵ�

#include<chrono>
#include "MainWindow.hpp"
#include "RenderEngine.h"
#include<iostream>

//֡�� ʵʱ���㷨
void callFre() {
	static std::chrono::high_resolution_clock::time_point pre = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point nowTime = std::chrono::high_resolution_clock::now();
	int fp = static_cast<int>(1.f / (double)(nowTime - pre).count() * 1000 * 1000 * 1000);
	pre = nowTime;
}


int main() {
	
	if (CAIEngine.initial())
		return -1;
	
	MainWindow mWindow(1000,800);
	mWindow.init();
	CAIEngine.addRenderWindow(&mWindow);
	CAIEngine.start();
	return 0;
}