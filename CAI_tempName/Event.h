#pragma once
#include "Object.h"
//using event = void (*)(GLFWwindow* window, double xoffset, double yoffset);
//事件系统是很好开发的。原因在于一个窗口的渲染是单线程的，不存在数据竞争问题
//需要获取的固定状态有：键盘数据，鼠标数据。键盘只有按下问题，鼠标则有位置和按下两个数据需要处理
//那么有两种方式：一种是GLFW的事件，在他的基础上注册回调，然后生成自己的事件放入事件队列里。
//另一种是轮询的方式
class EventArgs {
public:
	Object* who;
	Object* value;
};
enum EventType
{
	Tunnel,
	Bubble
};
class Event {
public:
	EventArgs args;
};