#include"caipch.h"
#include "RenderEngine.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Application.h"
#include "PaintDevice.h"
#include "Shader.h"
#include "Character.h"
#include "Controls/ContentControls/Window.h"
#include "log/Log.h"

RenderEngine::RenderEngine() noexcept : mainWinHd(NULL), font(nullptr), fontShader(nullptr), rectShader(nullptr)
{
	name = CAISTR(RenderEngine);
}

RenderEngine::~RenderEngine() noexcept
{
	if (font != nullptr)
		delete font;
	if (fontShader != nullptr)
		delete fontShader;
	if (rectShader != nullptr)
		delete rectShader;
	for (auto& painter : pDevice)
		delete painter;
	for (auto& win : glfwWindows)
		glfwDestroyWindow(win);
	glfwTerminate();
}

bool RenderEngine::InitGuiEnvironment()
{
	if (glfwInit() == GLFW_FALSE){
		LogError("glfw init false");
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}

bool RenderEngine::LoadGLFunction()
{
	glfwMakeContextCurrent(mainWinHd);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LogError("Failed to initialize GLAD");
		return false;
	}
	return true;
}

bool RenderEngine::LoadShader()
{
	font = new Font();
	fontShader = new Shader("resources/Shaders/TextVertexShader.glsl", "resources/Shaders/TextFragmentShader.glsl", "");
	rectShader = new Shader("resources/Shaders/RectVertexShader.glsl", "resources/Shaders/RectFragmentShader.glsl", "resources/Shaders/RectGeometryShader.glsl");
	return true;
}


void RenderEngine::Start(void) {
	RenderLoop();
}

GLFWwindow* RenderEngine::CreatWindow(int width, int height, const char* title)
{
	GLFWwindow* window = nullptr;
	if (mainWinHd == nullptr) {
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		mainWinHd = window;
		if (!LoadGLFunction()) {
			glfwDestroyWindow(window);
			mainWinHd = nullptr;
			return nullptr;
		}
		LoadShader();
	}
	else {
		window = glfwCreateWindow(width, height, title, NULL, mainWinHd);
	}
	glfwWindows.emplace_back(window);
	return window;
}

void RenderEngine::AddRenderWindow(Window* win)
{
	windows.emplace_back(win);
	glfwSetWindowUserPointer(win->getWinHD(), win);
	glfwSetCursorPosCallback(win->getWinHD(), MouseMoveCallBack);
	glfwSetMouseButtonCallback(win->getWinHD(), MouseButtonCallBack);
	glfwSetCharCallback(win->getWinHD(), TextInputCallBack);
	glfwSetKeyCallback(win->getWinHD(), KeyInputCallBack);
	glfwSetCursorEnterCallback(win->getWinHD(), LeaveWindowCallBack);
}

void RenderEngine::SetWindowSize(GLFWwindow* win, int width, int height)
{
	glfwSetWindowSize(win, width, height);
	//当指定，opengl会自动将视口绑定到上下文所指定的窗口大小
	//但后期设置窗口视口大小并不会自动更改
	glViewport(0, 0, width, height);
}

void RenderEngine::SetWindowProjection(const Math::TransMatrix& mt)
{
	rectShader->SetMat4("projection", mt);
	fontShader->SetMat4("projection", mt);
}

void RenderEngine::SetColorProjection(const Math::TransMatrix& mt)
{
	rectShader->SetMat4("projection_color", mt);
	fontShader->SetMat4("projection_color", mt);
}

void RenderEngine::SetColorProjection(float* mt)
{
	rectShader->SetMat4("projection_color", mt);
	fontShader->SetMat4("projection_color", mt);
}

PaintDevice* RenderEngine::CreatePaintDevice()
{
	auto device = new PaintDevice();
	device->font = font;
	device->fontShader = fontShader;
	device->shader = rectShader;
	device->Init();
	pDevice.emplace_back(device);
	return device;
}

//void RenderEngine::SetWindowProjection(const Math::TransMatrix& mt)
//{
//	squareShader->SetMat4("projection", mt);
//	fontShader->SetMat4("projection", mt);
//}
//
//void RenderEngine::SetColorProjection(const Math::TransMatrix& mt)
//{
//	squareShader->SetMat4("projection_color", mt);
//	fontShader->SetMat4("projection_color", mt);
//}
//
//void RenderEngine::SetColorProjection(float* mt)
//{
//	squareShader->SetMat4("projection_color", mt);
//	fontShader->SetMat4("projection_color", mt);
//}

void RenderEngine::RenderLoop(void)
{
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearStencil(0);
	glStencilFunc(GL_ALWAYS, 0, 0xff);
	while (!glfwWindowShouldClose(mainWinHd))
	{
		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		for (auto& win : windows) {
			glfwMakeContextCurrent(win->getWinHD());
			win->Render();
			glfwSwapBuffers(win->getWinHD());
		}
		glfwPollEvents();
	}
}