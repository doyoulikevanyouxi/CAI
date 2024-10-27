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
namespace CAITF {
	class EventAbstract;
}
class RenderEngine final : public Object
{
	friend class PaintDevice;
public:
	struct EventArgs
	{
		CAITF::EventAbstract* event;
		GLFWwindow* winHD;
	};
public:
	RenderEngine() noexcept;
	~RenderEngine() noexcept;
	
public:
	uint32_t initial(void);
	void start(void);
	GLFWwindow* creatWindow(int width, int height, const char* title);
	inline GLFWwindow* getMainWindow() { return alreadyOn && !mainWHasToken ? mainWinHd : NULL; }
	inline Font* getFont() noexcept { return font; }
	bool windowClose(GLFWwindow* win);
	void activateWindow(GLFWwindow* win);
	void addRenderWindow(Window* win);
	void setWindowPossition(GLFWwindow* win, int x, int y);
	void setWindowSize(GLFWwindow* win,int width,int height);
	void setWindowProjection(const Math::TransMatrix& mt);
	void setColorProjection(const Math::TransMatrix& mt);
	void setColorProjection(float* mt);
	void EventDistribute(EventArgs& eArgs);
	void EventReDistribute(CAITF::EventAbstract& event);
private:
	Window* findWindowByHD(GLFWwindow* HD);
private:
	//����Ⱦѭ��ͳһ�����Ǻ��鷳����
	//������һ�����ڽ������ݸ��£���������bug
	void renderLoop(void);
private:
	GLFWwindow* mainWinHd;
	Shader* squareShader;
	Shader* fontShader;
	Shader* templateShader;
	Font* font;
	std::vector<Window*> windows;
	EventArgs* eventArgs;
public:
	bool alreadyOn;
	bool mainWHasToken;
};

extern RenderEngine CAIEngine;