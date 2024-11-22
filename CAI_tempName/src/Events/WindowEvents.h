#pragma once
#include "EventAbstract.h"
class WindowsEvent :public EventAbstract {};
class WindowResizeEvent : public WindowsEvent {
public:
	WindowResizeEvent(unsigned int width, unsigned height) noexcept :width(width), height(height) {

	}
public:
	inline unsigned int Width() const noexcept { return width; }
	inline unsigned int Height() const noexcept { return height; }
	const std::string ToString() const override {
		std::string str = "WindowResizeEvent:" + std::to_string(width) + std::to_string(height);
		return str;
	}

	Event_Class_Type(WindowResizeEvent)
protected:
	unsigned int width;
	unsigned int height;
};
