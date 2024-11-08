#include "caipch.h"
#include "Input.h"
#include "Events/Events.h"
#include "UI/RenderEngine.h"
#include <glfw3.h>
Input Input::ipt;

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (Input::GetInstance().InputMode() == Input::Mode::TextInput)
		return;
	switch (action)
	{
	case GLFW_PRESS:
	{
		CAITF::KeyPressedEvent e(key,0);
		Input::GetInstance().RaiseInputEvent(window, e);
	}
		break;
	case GLFW_RELEASE:
	{
		CAITF::KeyUpEvent e(key);
		Input::GetInstance().RaiseInputEvent(window, e);
	}
		break;
	case GLFW_REPEAT:
	{
		CAITF::KeyPressedEvent e(key, 1);
		Input::GetInstance().RaiseInputEvent(window, e);
	}
		break;
	default:
		break;
	}

}

void TextCallBack(GLFWwindow* window, unsigned int codepoint)
{
	CAITF::TextInputEvent e(codepoint);
	Input::GetInstance().RaiseInputEvent(window,e);

	
}

void Input::RaiseInputEvent(GLFWwindow* window,CAITF::InputEvent& event)
{
	RenderEngine::EventArgs eArgs;
	eArgs.event = (CAITF::EventAbstract*)&event;
	eArgs.winHD = window;
	CAIEngine.EventDistribute(eArgs);
}
