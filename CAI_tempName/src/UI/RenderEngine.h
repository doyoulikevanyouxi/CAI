//��Ⱦ���棬������Opengl�Ĳ������𲻹�
//������ʱ����������ݵĲ��������潫��
//�����ݲ����ϲ���ͬʱ��δ���ж��߳̿�
//��������Ŀǰ��˵���д��ڵ���Ⱦ����ͬ
//һ���߳��У����ڽ���Բ�ͬ���ڿ�����
//ͬ���߳���Ӧ������ѹ��

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
	//����Ⱦѭ��ͳһ�����Ǻ��鷳����
	//������һ�����ڽ������ݸ��£���������bug
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

