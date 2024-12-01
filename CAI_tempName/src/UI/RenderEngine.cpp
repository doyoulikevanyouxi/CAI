#include"caipch.h"
#include "RenderEngine.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Character.h"
#include "UI/PaintDeivces/PaintDevice.h"
#include "Controls/ContentControls/Window.h"
#include "Application.h"

#include "log/log.h"
RenderEngine::RenderEngine() noexcept : mainWinHd(nullptr), squareShader(nullptr), fontShader(nullptr), lineShader(nullptr),
font(nullptr),initComplete(false)
{
	name = CAISTR(RenderEngine);
}

RenderEngine::~RenderEngine() noexcept
{
	if (squareShader != nullptr)
		delete squareShader;
	if (fontShader != nullptr)
		delete fontShader;
	if (font != nullptr)
		delete font;
	//for (auto& win : glfwWindws)
	//	glfwDestroyWindow(win);
	for (auto& pDevice : paintDevices)
		delete pDevice;
	glfwTerminate();
}

bool RenderEngine::InitGUIEnvironment()
{
	if (glfwInit() == GLFW_FALSE) {
		LogError("GLFW init failed");
		return false;
	}
	LogNotice("GLFW init finished");
	return true;
}

inline bool RenderEngine::InitGLFunction()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LogError("GLAD init failed");
		return false;
	}
	LogNotice("GLAD init finished");

	return true;
}

inline bool RenderEngine::InitResources()
{
	squareShader = new Shader("resources/Shaders/RectVertexShader.glsl", "resources/Shaders/RectFragmentShader.glsl", "resources/Shaders/RectGeometryShader.glsl");
	if (!squareShader->ComplieShader()) {
		delete squareShader;
		squareShader = nullptr;
		return false;
	}
	fontShader = new Shader("resources/Shaders/TextVertexShader.glsl", "resources/Shaders/TextFragmentShader.glsl", "");
	if (!fontShader->ComplieShader()) {
		delete squareShader;
		squareShader = nullptr;
		delete fontShader;
		fontShader = nullptr;
		return false;
	}
	lineShader = new Shader("resources/Shaders/LineVertexShader.glsl", "resources/Shaders/LineFragmentShader.glsl", "resources/Shaders/LineGeometryShader.glsl");
	lineShader->ComplieShader();
	font = new Font();
	return true;
}

GLFWwindow* RenderEngine::GLCreateWindow(int width, int height, const char* title)
{
	if (mainWinHd == nullptr) {
		auto window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwMakeContextCurrent(window);
		if (!InitGLFunction()) {
			if (window != nullptr)
				glfwDestroyWindow(window);
			return nullptr;
		}
		if (!InitResources()) {
			if (window != nullptr)
				glfwDestroyWindow(window);
			return nullptr;
		}
		mainWinHd = window;
		initComplete = true;
		glfwWindws.emplace_back(window);
		return window;
	}
	auto window = glfwCreateWindow(width, height, title, NULL, mainWinHd);
	glfwWindws.emplace_back(window);
	return window;
}

PaintDevice* RenderEngine::GetPaintDevice()
{
	if (!initComplete)
		return nullptr;
	PaintDevice* device = new PaintDevice();
	device->fontShader = fontShader;
	device->rectShader = squareShader;
	device->geometryShader = lineShader;
	paintDevices.emplace_back(device);
	return device;
}

void RenderEngine::Start(void) {
	RenderLoop();
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

void RenderEngine::SetWindowProjection(const Math::mat4& mt)
{
	squareShader->SetMat4("projection", mt);
	fontShader->SetMat4("projection", mt);
	lineShader->SetMat4("projection", mt);
}


void RenderEngine::SetColorProjection(float mt)
{
	squareShader->SetFloat("colorResolution", mt);
	fontShader->SetFloat("colorResolution", mt);
	lineShader->SetFloat("colorResolution", mt);
	
}


void RenderEngine::SetResolution(float width, float height)
{
	
	squareShader->SetVec2("iResolution", width,height);
	fontShader->SetVec2("iResolution", width, height);
	lineShader->SetVec2("iResolution", width, height);
}

Window* RenderEngine::FindWindowByHD(GLFWwindow* HD)
{
	for (auto& win : windows) {
		if (win->getWinHD() == HD)
			return win;
	}
	return nullptr;
}

void RenderEngine::RenderLoop(void)
{
	if (!initComplete)
		return;

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
			squareShader->Use();
			win->Render();
			glfwSwapBuffers(win->getWinHD());
		}
		glfwPollEvents();
	}
}

