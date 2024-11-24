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
class PaintDevice;
class Shader;
class Font;
class Window;
class EventAbstract;
class RenderEngine final : public Object
{
	friend class Application;
private:
	RenderEngine() noexcept;
	~RenderEngine() noexcept;

public:
	bool InitGuiEnvironment();
	bool LoadGLFunction();
	bool LoadShader();
	void Start(void);
	GLFWwindow* CreatWindow(int width, int height, const char* title);
	inline Font* GetFont() noexcept { return font; }
	void AddRenderWindow(Window* win);
	void SetWindowSize(GLFWwindow* win, int width, int height);
	void SetWindowProjection(const Math::TransMatrix& mt);
	void SetColorProjection(const Math::TransMatrix& mt);
	void SetColorProjection(float* mt);
public:
	PaintDevice* CreatePaintDevice();
private:
	//����Ⱦѭ��ͳһ�����Ǻ��鷳����
	//������һ�����ڽ������ݸ��£���������bug
	void RenderLoop(void);
private:
	Font* font;
	Shader* fontShader;
	Shader* rectShader;
	GLFWwindow* mainWinHd;
	std::deque<GLFWwindow*> glfwWindows;
	std::deque<PaintDevice*> pDevice;
	std::vector<Window*> windows;
};