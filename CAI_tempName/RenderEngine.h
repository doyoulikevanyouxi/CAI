//��Ⱦ���棬������Opengl�Ĳ������𲻹�
//������ʱ����������ݵĲ��������潫��
//�����ݲ����ϲ���ͬʱ��δ���ж��߳̿�
//��������Ŀǰ��˵���д��ڵ���Ⱦ����ͬ
//һ���߳��У����ڽ���Բ�ͬ���ڿ�����
//ͬ���߳���Ӧ������ѹ��

#pragma once
#include "Object.h"
#include <vector>
class GLFWwindow;
class Shader;
class Window;
class RenderEngine final : public Object
{
public:
	RenderEngine() noexcept;
	~RenderEngine() noexcept;
public:
	uint32_t initial(void);
	void start(void);
	GLFWwindow* creatWindow(int width, int height, const char* title);
	inline GLFWwindow* getMainWindow() { return alreadyOn && !mainWHasToken ? mainWinHd : NULL; }
	bool windowClose(GLFWwindow* win);
	void activateWindow(GLFWwindow* win);
	void addRenderWindow(Window* win);
	void setWindowPossition(GLFWwindow* win, int x, int y);
	void setWindowSize(GLFWwindow* win,int width,int height);
private:
	void renderLoop(void);
private:
	GLFWwindow* mainWinHd;
	Shader* shd;
	std::vector<Window*> windows;
public:
	bool alreadyOn;
	bool mainWHasToken;
};

extern RenderEngine CAIEngine;