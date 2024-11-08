#pragma once
struct GLFWwindow;
namespace CAITF {
	class InputEvent;
}
void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
void TextCallBack(GLFWwindow* window, unsigned int codepoint);

class Input {

public:
	enum Mode
	{
		TextInput,
		Defualt
	};
public:
	inline static Input& GetInstance() noexcept { return ipt; }
	inline Mode InputMode() { return mode; }
	void RaiseInputEvent(GLFWwindow* window,CAITF::InputEvent& event);
private:
	Input() noexcept {}
	static Input ipt;
	Mode mode = Defualt;
};

