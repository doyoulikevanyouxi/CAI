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
/// <summary>
/// 渲染引擎
/// 用于初始化渲染环境，创建窗口以及创建渲染设备句柄
/// </summary>
class RenderEngine final : public Object
{
	friend class Application;
private:
	RenderEngine() noexcept;
	~RenderEngine() noexcept;
public:
	//初始化glfw库
	bool InitGUIEnvironment();
	//加载GL函数
	inline bool InitGLFunction();
	//初始化资源：字体库加载，着色器程序生成
	inline bool InitResources();
	//创建窗口
	GLFWwindow* GLCreateWindow(int width, int height, const char* title);
	//创建渲染设备
	PaintDevice* GetPaintDevice();
	//开始渲染循环
	void Start(void);
	//获取字体库
	inline Font* GetFont() noexcept { return font; }
	//为窗口绑定事件回调
	void AddRenderWindow(Window* win);
	//设置窗口大小
	void SetWindowSize(GLFWwindow* win, int width, int height);
	//设置窗口的投射矩阵
	void SetWindowProjection(const Math::TransMatrix& mt);
	//设置颜色的投射矩阵
	void SetColorProjection(const Math::TransMatrix& mt);
	void SetColorProjection(float* mt);
private:
	Window* FindWindowByHD(GLFWwindow* HD);
private:
	//将渲染循环统一起来是很麻烦的事
	//必须有一个窗口接受数据更新，否则默认的帧缓冲会导致数据膨胀，崩溃
	void RenderLoop(void);
private:
	//主窗口句柄
	GLFWwindow* mainWinHd;
	//矩形渲染着色器
	Shader* squareShader;
	//字体渲染着色器
	Shader* fontShader;
	//字体库
	Font* font;
	//创建的所有窗口的集合
	std::vector<GLFWwindow*> glfwWindws;
	//创建的所有绘制设备
	std::vector<PaintDevice*> paintDevices;
	//所有需要更新帧缓冲的窗口
	std::vector<Window*> windows;
private:
	bool initComplete;
public:
};

