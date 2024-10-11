//渲染引擎，对所有Opengl的操作负责不过
//这里暂时分离出对数据的操作，后面将会
//把数据操作合并。同时还未进行多线程开
//发，所以目前来说所有窗口的渲染都在同
//一个线程中，后期将会对不同窗口开启不
//同的线程以应对性能压力

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