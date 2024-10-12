#pragma once
#include "Object.h"
using event = void (*)(GLFWwindow* window, double xoffset, double yoffset);
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