//Glad�����ڻ�ȡOpengl����ָ���Ա�ʹ��Opengl����
//glfw���������ڴ������ڵ�
#include "caipch.h"
#include<chrono>
#include "MainWindow.hpp"
#include "UI/Application.h"
#include "log/Log.h"
//֡�� ʵʱ���㷨
void callFre() {
	static std::chrono::high_resolution_clock::time_point pre = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point nowTime = std::chrono::high_resolution_clock::now();
	int fp = static_cast<int>(1.f / (double)(nowTime - pre).count() * 1000 * 1000 * 1000);
	pre = nowTime;
}


int main() {
	Log::init();
	
	MainWindow mWindow(1000,800);
	if (!mWindow.Init())
		return -1;
	Application::app.Start();
	return 0;
}