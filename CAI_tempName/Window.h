//�����࣬�̳���ContentControl
//ֻ������Content���ԣ����ܶ���
//��Ӷ���ӿؼ�
//�ڿ����׶Σ���ʱ�Ƴ���Window��
//ѭ���������е�Windowѭ��ͳһ��
//һ�𣬺��ڽ������ÿ��Window��
//ѭ��
#pragma once
#include "ContentControl.h"
#include "Coordinate.h"
struct GLFWwindow;
class Window : public ContentControl
{
public:
	Window() noexcept;
	Window(int width, int height) noexcept;
	virtual ~Window() noexcept;
public:
	void activited();
	void show();
	GLFWwindow* getWinHD() noexcept;
	void init() noexcept;
public:
	void setSize(int width, int height) noexcept;
protected:
	//ʹ�ô��ڱ������Ⱦѭ������Ҫ��ѭ�����õ���ͬ���߳���
	void renderLoop() noexcept;
protected:
	GLFWwindow* winHd;
	Size size;

};

