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
	virtual ~Window() noexcept;
public:
	void activited();
	void show();
	GLFWwindow* getWinHD() noexcept;
public:
	void setSize(int width, int height) noexcept;
protected:
	GLFWwindow* winHd;
	Size size;
};

