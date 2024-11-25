//渲染引擎，对所有Opengl的操作负责不过
//这里暂时分离出对数据的操作，后面将会
//把数据操作合并。同时还未进行多线程开
//发，所以目前来说所有窗口的渲染都在同
//一个线程中，后期将会对不同窗口开启不
//同的线程以应对性能压力

#pragma once
#include "Object.h"
#include "Mathmatics/Math.hpp"
struct GLFWwindow;
class Shader;
class Font;
class Window;
class EventAbstract;
class PaintDevice;
class RenderEngine final : public Object
{
	friend class Application;
private:
	RenderEngine() noexcept;
	~RenderEngine() noexcept;
public:
	bool InitGUIEnvironment();
	inline bool InitGLFunction();
	inline bool InitResources();
	GLFWwindow* GLCreateWindow(int width, int height, const char* title);
	PaintDevice* GetPaintDevice();
	void Start(void);
	inline Font* GetFont() noexcept { return font; }
	void AddRenderWindow(Window* win);
	void SetWindowSize(GLFWwindow* win, int width, int height);
	void SetWindowProjection(const Math::TransMatrix& mt);
	void SetColorProjection(const Math::TransMatrix& mt);
	void SetColorProjection(float* mt);
private:
	Window* FindWindowByHD(GLFWwindow* HD);
private:
	//将渲染循环统一起来是很麻烦的事
	//必须有一个窗口接受数据更新，否则会出先bug
	void RenderLoop(void);
private:
	GLFWwindow* mainWinHd;
	Shader* squareShader;
	Shader* fontShader;
	Font* font;
	std::vector<GLFWwindow*> glfwWindws;
	std::vector<PaintDevice*> paintDevices;
	std::vector<Window*> windows;
private:
	bool initComplete;
public:
};

