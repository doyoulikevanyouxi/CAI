//�����࣬�̳���ContentControl
//ֻ������Content���ԣ����ܶ���
//��Ӷ���ӿؼ�
//�ڿ����׶Σ���ʱ�Ƴ���Window��
//ѭ���������е�Windowѭ��ͳһ��
//һ�𣬺��ڽ������ÿ��Window��
//ѭ��
#pragma once
#include "../ContentControl.h"
#include "Datas/Coordinate.h"
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
	bool Init() override;
	GLFWwindow* getWinHD() noexcept;
	void SetSize(int width, int height) noexcept;
protected:
	GLFWwindow* winHd;
	Size size;

};

