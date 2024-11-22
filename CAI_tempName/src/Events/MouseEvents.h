#pragma once
#include "EventAbstract.h"
class MouseButtonEvent :public EventAbstract {
public:
	Event_Class_PreType(EventType::MouseButtonEvent)
protected:
	MouseButtonEvent(int button) noexcept : button(button) {}
protected:
	int button;
};

/// <summary>
/// ����ƶ��¼�
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
/// ����ٿؼ��ڵ��ƶ��¼�
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
/// �������¼�
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
/// ����뿪�¼�
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




/// <summary>
/// ��갴ť�����¼�
/// </summary>
class MouseButtonPressedEvent : public MouseButtonEvent {
public:
	MouseButtonPressedEvent(int button, bool repeat) noexcept :MouseButtonEvent(button), repeat(repeat) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseButtonPressedEvent:" + std::to_string(button) + std::to_string(repeat);
		return str;
	}
	Event_Class_PreType(EventType::MouseButtonEvent)
public:
	Event_Class_Type(MouseButtonPressedEvent)
private:
	bool repeat;
};

/// <summary>
/// ��갴ť�����¼�
/// </summary>
class MouseButtonUpEvent : public MouseButtonEvent {
public:
	MouseButtonUpEvent(int button) noexcept :MouseButtonEvent(button) {}
public:
	const std::string ToString() const override {
		std::string str = "MouseButtonPressedEvent:" + std::to_string(button);
		return str;
	}
	Event_Class_Type(MouseButtonUpEvent)
private:
	bool repeat;
};