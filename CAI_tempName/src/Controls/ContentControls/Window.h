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
	GLFWwindow* getWinHD() noexcept;
public:
	void SetSize(int width, int height) noexcept;
	void Init();
protected:
	virtual void InitializeComponents();
	//ʹ�ô��ڱ������Ⱦѭ������Ҫ��ѭ�����õ���ͬ���߳���
	void RenderLoop() noexcept;

protected:
	GLFWwindow* winHd;
	Size size;
private:
	bool initialConponentsDone = false;
};

