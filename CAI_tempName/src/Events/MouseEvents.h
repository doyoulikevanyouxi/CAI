#pragma once
#include "EventAbstract.h"

#define MOUSE_UP	  0
#define MOUSE_PRESS 1

#define MOUSE_BUTTON_1 1
#define MOUSE_BUTTON_2 2
#define MOUSE_BUTTON_3 3
#define MOUSE_BUTTON_4 4
#define MOUSE_BUTTON_5 5
#define MOUSE_BUTTON_6 6
#define MOUSE_LEFT_BUTTON		MOUSE_BUTTON_1
#define MOUSE_RIGHT_BUTTON		MOUSE_BUTTON_2
#define MOUSE_MIDDLE_BUTTON	MOUSE_BUTTON_3

class MouseButtonEvent :public EventAbstract {
public:
	Event_Class_PreType(EventType::MouseButtonEvent)
protected:
	MouseButtonEvent(int button) noexcept : button(button) {}
public:
	inline int MButton() const { return button; }
protected:
	int button;
};

/// <summary>
/// 鼠标移动事件
/// </summary>
class MouseMoveEvent : public EventAbstract {
public:
	MouseMoveEvent(unsigned int x, unsigned int y) :x(x), y(y) {

	}
	Event_Class_PreType(EventType::Defualt)
public:
	const unsigned int& X() const  noexcept { return x; }
 	const unsigned int& Y() const  noexcept { return y; }
public:
	const std::string ToString() const override {
		std::string str = "MouseMoveEvent:" + std::to_string(x) + "," + std::to_string(y);
		return str;
	}
	Event_Class_Type(MouseMoveEvent)
private:
	const unsigned int x;
	const unsigned int y;
};

class PreMouseOverEvent : public EventAbstract {
public:
	PreMouseOverEvent(unsigned int x, unsigned int y) :x(x), y(y) {

	}
	Event_Class_PreType(EventType::Defualt)
public:
	const unsigned int& X() const  noexcept { return x; }
	const unsigned int& Y() const  noexcept { return y; }
public:
	const std::string ToString() const override {
		std::string str = "MouseMoveEvent:" + std::to_string(x) + "," + std::to_string(y);
		return str;
	}
	Event_Class_Type(PreMouseOverEvent)
private:
	const unsigned int x;
	const unsigned int y;
};


/// <summary>
/// 鼠标再控件内的移动事件
/// </summary>
class MouseOverEvent : public EventAbstract {
public:
	MouseOverEvent(unsigned int x, unsigned int y) :x(x), y(y) {

	}
	Event_Class_PreType(EventType::Defualt)
public:
	const unsigned int& X() const  noexcept { return x; }
	const unsigned int& Y() const  noexcept { return y; }
public:
	const std::string ToString() const override {
		std::string str = "MouseMoveEvent:" + std::to_string(x) + "," + std::to_string(y);
		return str;
	}
	Event_Class_Type(MouseOverEvent)
private:
	const unsigned int x;
	const unsigned int y;
};


/// <summary>
/// 鼠标进入事件
/// </summary>
class MouseEnterEvent : public EventAbstract {
public:
	MouseEnterEvent() {}
	Event_Class_PreType(EventType::Defualt)
public:
	Event_Class_Type(MouseEnterEvent)
public:
	const std::string ToString() const override {
		std::string str = "MouseEnterEvent" ;
		return str;
	}
};

/// <summary>
/// 鼠标离开事件
/// </summary>
class MouseLeaveEvent : public EventAbstract {
public:
	MouseLeaveEvent() {}
	Event_Class_PreType(EventType::Defualt)
public:
	Event_Class_Type(MouseLeaveEvent)
public:
	const std::string ToString() const override {
		std::string str = "MouseLeaveEvent:";
		return str;
	}
};


class PreMouseButtonDownEvent :public MouseButtonEvent {
public:
	PreMouseButtonDownEvent(int button, bool repeat) noexcept :MouseButtonEvent(button), repeat(repeat) {}
public:
	const std::string ToString() const override {
		std::string str = "PreMouseButtonDownEvent:" + std::to_string(button) + std::to_string(repeat);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(PreMouseButtonDownEvent)
private:
	bool repeat;
};


class MouseLeftButtonDownEvent : public MouseButtonEvent {
public:
	MouseLeftButtonDownEvent(bool repeat) noexcept :MouseButtonEvent(MOUSE_LEFT_BUTTON), repeat(repeat) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseLeftButtonDownEvent:"  + std::to_string(repeat);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(MouseLeftButtonDownEvent)
private:
	bool repeat;

};

class MouseRightButtonDownEvent : public MouseButtonEvent {
public:
	MouseRightButtonDownEvent(bool repeat) noexcept :MouseButtonEvent(MOUSE_RIGHT_BUTTON), repeat(repeat) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseRightButtonDownEvent:" + std::to_string(repeat);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(MouseLeftButtonDownEvent)
private:
	bool repeat;
};

class MouseMiddleButtonDownEvent : public MouseButtonEvent {
public:
	MouseMiddleButtonDownEvent(bool repeat) noexcept :MouseButtonEvent(MOUSE_MIDDLE_BUTTON), repeat(repeat) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseMiddleButtonDownEvent:" + std::to_string(repeat);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(MouseMiddleButtonDownEvent)
private:
	bool repeat;
};

class PreMouseButtonUpEvent : public MouseButtonEvent {
public:
	PreMouseButtonUpEvent(int button) noexcept :MouseButtonEvent(button){}
public:
	const std::string ToString() const override {
		std::string str = "PreMouseButtonUpEvent:" + std::to_string(button);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(PreMouseButtonUpEvent)
};


class MouseLeftButtonUpEvent : public MouseButtonEvent {
public:
	MouseLeftButtonUpEvent() noexcept :MouseButtonEvent(MOUSE_LEFT_BUTTON) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseLeftButtonUpEvent:" + std::to_string(button);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(MouseLeftButtonUpEvent)
};

class MouseRightButtonUpEvent : public MouseButtonEvent {
public:
	MouseRightButtonUpEvent() noexcept :MouseButtonEvent(MOUSE_RIGHT_BUTTON) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseRightButtonUpEvent:" + std::to_string(button);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(MouseRightButtonUpEvent)
};

class MouseMiddleButtonUpEvent : public MouseButtonEvent {
public:
	MouseMiddleButtonUpEvent() noexcept :MouseButtonEvent(MOUSE_RIGHT_BUTTON) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseMiddleButtonUpEvent:" + std::to_string(button);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(MouseMiddleButtonUpEvent)
};