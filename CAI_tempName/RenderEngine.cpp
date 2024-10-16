#include "RenderEngine.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Character.h"
#include <iostream>
#include "Window.h"
using namespace std;
RenderEngine::RenderEngine() noexcept : mainWinHd(NULL), squareShader(nullptr), fontShader(nullptr), 
									font(nullptr), alreadyOn(false), mainWHasToken(false)
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
	squareShader = new Shader("./square_shader.sha");
	fontShader = new Shader("./text_shader.sha");
	font = new Font();
	squareShader->use();
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

void RenderEngine::setWindowProjection(const Math::TransMatrix& mt)
{
	squareShader->setMat4("projection", mt);
	fontShader->setMat4("projection", mt);
}

void RenderEngine::setColorProjection(const Math::TransMatrix& mt)
{
	squareShader->setMat4("projection_color", mt);
}

void RenderEngine::setColorProjection(float* mt)
{
	squareShader->setMat4("projection_color", mt);
}


void RenderEngine::renderLoop(void)
{
	if (!alreadyOn)
		return;

	while (!glfwWindowShouldClose(mainWinHd))
	{
		glClearColor(1.f,1.f,1.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& win : windows) {

			glfwMakeContextCurrent(win->getWinHD());
			squareShader->use();
			win->render();
			glfwSwapBuffers(win->getWinHD());
		}
		glfwPollEvents();
	}
}

RenderEngine CAIEngine;