#include"caipch.h"
#include "RenderEngine.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Character.h"
#include "Controls/ContentControls/Window.h"
#include "Events/Events.h"
#include "Input/Input.h"
using namespace std;
RenderEngine::RenderEngine() noexcept : mainWinHd(NULL), squareShader(nullptr), fontShader(nullptr),
									font(nullptr), alreadyOn(false), mainWHasToken(false), eventArgs(new EventArgs)
{
	name = "RenderEngine";
}

RenderEngine::~RenderEngine() noexcept
{
	if (squareShader != nullptr)
		delete squareShader;
	if (fontShader != nullptr)
		delete fontShader;
	if (font != nullptr)
		delete font;
	if (eventArgs != nullptr)
		delete eventArgs;
	glfwTerminate();
}

uint32_t RenderEngine::Initial(void)
{
	if (glfwInit() == GLFW_FALSE) {
		cout << "glfw init false" << endl;
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mainWinHd = glfwCreateWindow(800, 600, "CAITF(TEMP)", NULL, NULL);
	if (mainWinHd == NULL)
	{
		cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 2;
	}
	//必须有上下文后才能使用GL函数，此时导入GL函数才不会出错
	glfwMakeContextCurrent(mainWinHd);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return 3;
	}
	/*std::cout << glGetString(GL_VERSION) << std::endl;
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum  of vertex attributes supported: " << nrAttributes << std::endl;*/
	squareShader = new Shader("resources/Shaders/RectVertexShader.glsl", "resources/Shaders/RectFragmentShader.glsl","");
	fontShader = new Shader("resources/Shaders/TextVertexShader.glsl", "resources/Shaders/TextFragmentShader.glsl", "");
	font = new Font();
	squareShader->Use();
	alreadyOn = true;
	return 0;
}


void RenderEngine::Start(void) {
	RenderLoop();
}

GLFWwindow* RenderEngine::CreatWindow(int width, int height, const char* title)
{
	return glfwCreateWindow(width, height, title, NULL, NULL);
}

bool RenderEngine::WindowClose(GLFWwindow* win)
{
	return glfwWindowShouldClose(win) ? true:false;
}

void RenderEngine::ActivateWindow(GLFWwindow* win)
{
	glfwMakeContextCurrent(win);
	
}

void RenderEngine::AddRenderWindow(Window* win)
{
	windows.emplace_back(win);
	glfwSetWindowUserPointer(win->getWinHD(), this);
	glfwSetCursorPosCallback(mainWinHd, [](GLFWwindow* window, double xpos, double ypos) {
		RenderEngine* ev = (RenderEngine*)glfwGetWindowUserPointer(window);
		CAITF::MouseMoveEvent e(xpos, ypos);
		EventArgs eArgs;
		eArgs.event = (CAITF::EventAbstract*)&e;
		eArgs.winHD = window;
		ev->EventDistribute(eArgs);
		});
	glfwSetCharCallback(mainWinHd, TextCallBack);
	glfwSetKeyCallback(mainWinHd, KeyCallBack);
}

void RenderEngine::SetWindowPossition(GLFWwindow* win, int x, int y)
{
	glfwSetWindowPos(win, x, y);
}

void RenderEngine::SetWindowSize(GLFWwindow* win, int width, int height)
{
	glfwSetWindowSize(win, width, height);
	glfwMakeContextCurrent(win);
	//当指定，opengl会自动将视口绑定到上下文所指定的窗口大小
	//但后期设置窗口视口大小并不会自动更改
	glViewport(0, 0, width, height);
}

void RenderEngine::SetWindowProjection(const Math::TransMatrix& mt)
{
	squareShader->SetMat4("projection", mt);
	fontShader->SetMat4("projection", mt);
}

void RenderEngine::SetColorProjection(const Math::TransMatrix& mt)
{
	squareShader->SetMat4("projection_color", mt);
	fontShader->SetMat4("projection_color", mt);
}

void RenderEngine::SetColorProjection(float* mt)
{
	squareShader->SetMat4("projection_color", mt);
	fontShader->SetMat4("projection_color", mt);
}

void RenderEngine::EventDistribute(EventArgs& eArgs)
{
	Window* win = FindWindowByHD(eArgs.winHD);
	if (win == nullptr)
		return;
	win->RaiseEvent(*(eArgs.event));
}

void RenderEngine::EventReDistribute(CAITF::EventAbstract& event)
{
	if (event.target == nullptr)
		return;
	((UIElement*)event.target)->RaiseEvent(event);
}

Window* RenderEngine::FindWindowByHD(GLFWwindow* HD)
{
	for(auto& win : windows){
		if (win->getWinHD() == HD)
			return win;
	}
	return nullptr;
}

void RenderEngine::RenderLoop(void)
{
	if (!alreadyOn)
		return;
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	while (!glfwWindowShouldClose(mainWinHd))
	{
		glClearColor(1.f,1.f,1.f,1.f);
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

RenderEngine CAIEngine;