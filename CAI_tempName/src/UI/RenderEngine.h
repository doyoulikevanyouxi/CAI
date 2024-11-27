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
/// <summary>
/// ��Ⱦ����
/// ���ڳ�ʼ����Ⱦ���������������Լ�������Ⱦ�豸���
/// </summary>
class RenderEngine final : public Object
{
	friend class Application;
private:
	RenderEngine() noexcept;
	~RenderEngine() noexcept;
public:
	//��ʼ��glfw��
	bool InitGUIEnvironment();
	//����GL����
	inline bool InitGLFunction();
	//��ʼ����Դ���������أ���ɫ����������
	inline bool InitResources();
	//��������
	GLFWwindow* GLCreateWindow(int width, int height, const char* title);
	//������Ⱦ�豸
	PaintDevice* GetPaintDevice();
	//��ʼ��Ⱦѭ��
	void Start(void);
	//��ȡ�����
	inline Font* GetFont() noexcept { return font; }
	//Ϊ���ڰ��¼��ص�
	void AddRenderWindow(Window* win);
	//���ô��ڴ�С
	void SetWindowSize(GLFWwindow* win, int width, int height);
	//���ô��ڵ�Ͷ�����
	void SetWindowProjection(const Math::TransMatrix& mt);
	//������ɫ��Ͷ�����
	void SetColorProjection(const Math::TransMatrix& mt);
	void SetColorProjection(float* mt);
private:
	Window* FindWindowByHD(GLFWwindow* HD);
private:
	//����Ⱦѭ��ͳһ�����Ǻ��鷳����
	//������һ�����ڽ������ݸ��£�����Ĭ�ϵ�֡����ᵼ���������ͣ�����
	void RenderLoop(void);
private:
	//�����ھ��
	GLFWwindow* mainWinHd;
	//������Ⱦ��ɫ��
	Shader* squareShader;
	//������Ⱦ��ɫ��
	Shader* fontShader;
	//�����
	Font* font;
	//���������д��ڵļ���
	std::vector<GLFWwindow*> glfwWindws;
	//���������л����豸
	std::vector<PaintDevice*> paintDevices;
	//������Ҫ����֡����Ĵ���
	std::vector<Window*> windows;
private:
	bool initComplete;
public:
};

