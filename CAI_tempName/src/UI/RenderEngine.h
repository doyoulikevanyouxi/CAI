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
class RenderEngine final : public Object
{
	friend class PaintDevice;
public:
	RenderEngine() noexcept;
	~RenderEngine() noexcept;

public:
	uint32_t Initial(void);
	void Start(void);
	GLFWwindow* CreatWindow(int width, int height, const char* title);
	inline GLFWwindow* GetMainWindow() { return alreadyOn && !mainWHasToken ? mainWinHd : NULL; }
	inline Font* GetFont() noexcept { return font; }
	bool WindowClose(GLFWwindow* win);
	void ActivateWindow(GLFWwindow* win);
	void AddRenderWindow(Window* win);
	void SetWindowPossition(GLFWwindow* win, int x, int y);
	void SetWindowSize(GLFWwindow* win, int width, int height);
	void SetWindowProjection(const Math::TransMatrix& mt);
	void SetColorProjection(const Math::TransMatrix& mt);
	void SetColorProjection(float* mt);
	void EventDistribute(Window*& win, EventAbstract& e);
	void EventReDistribute(EventAbstract& event);
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
	std::vector<Window*> windows;
public:
	bool alreadyOn;
	bool mainWHasToken;
};

extern RenderEngine CAIEngine;