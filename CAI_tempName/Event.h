#pragma once
#include "Object.h"
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