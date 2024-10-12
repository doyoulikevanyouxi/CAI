#include "RenderEngine.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include <iostream>
#include "Window.h"
using namespace std;
RenderEngine::RenderEngine() noexcept : mainWinHd(NULL), shd(nullptr), alreadyOn(false), mainWHasToken(false)
{
	name = "RenderEngine";

}

RenderEngine::~RenderEngine() noexcept
{
	if (shd != nullptr)
		delete shd;
	glfwTerminate();
}

uint32_t RenderEngine::initial(void)
{
	if (glfwInit() == GLFW_FALSE) {
		cout << "glfw init false" << endl;
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mainWinHd = glfwCreateWindow(800, 600, "CAI(TEMP)", NULL, NULL);
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
	std::cout << glGetString(GL_VERSION) << std::endl;
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum  of vertex attributes supported: " << nrAttributes << std::endl;
	shd = new Shader("./shaders.sha");
	shd->use();
	alreadyOn = true;
	return 0;
}


void RenderEngine::start(void) {
	renderLoop();
}

GLFWwindow* RenderEngine::creatWindow(int width, int height, const char* title)
{
	return glfwCreateWindow(width, height, title, NULL, NULL);
}

bool RenderEngine::windowClose(GLFWwindow* win)
{
	return glfwWindowShouldClose(win) ? true:false;
}

void RenderEngine::activateWindow(GLFWwindow* win)
{
	glfwMakeContextCurrent(win);
	
}

void RenderEngine::addRenderWindow(Window* win)
{
	windows.emplace_back(win);
}

void RenderEngine::setWindowPossition(GLFWwindow* win, int x, int y)
{
	glfwSetWindowPos(win, x, y);
}

void RenderEngine::setWindowSize(GLFWwindow* win, int width, int height)
{
	glfwSetWindowSize(win, width, height);
	glfwMakeContextCurrent(win);
	//当指定，opengl会自动将视口绑定到上下文所指定的窗口大小
	//但后期设置窗口视口大小并不会自动更改
	glViewport(0, 0, width, height);
}

void RenderEngine::renderLoop(void)
{
	if (!alreadyOn)
		return;
	while (!glfwWindowShouldClose(mainWinHd))
	{
		glClearColor(0.f,0.f,0.f,0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);
		
		for (auto& win : windows) {
			glfwMakeContextCurrent(win->getWinHD());
			win->render();
			glfwSwapBuffers(win->getWinHD());
		}
		glfwPollEvents();
	}
}

RenderEngine CAIEngine;