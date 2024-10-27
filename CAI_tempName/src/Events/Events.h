#pragma once

#include "EventAbstract.h"
namespace CAITF {
	class WindowsEvent :public EventAbstract {};
	class KeybordEvent :public EventAbstract {
	public:
		inline int KeyCode() const noexcept { return key; }
		Event_Class_PreType(EventType::KeybordEvent)
	protected:
		KeybordEvent(int key) noexcept : key(key) {}
	protected:
		int key;
	};
	class MouseButtonEvent :public EventAbstract {
	protected:
		MouseButtonEvent(int button) noexcept : button(button){}
	protected:
		int button;
	};

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
	class KeyPressedEvent : public KeybordEvent {
	public:
		KeyPressedEvent(int key, bool repeat) noexcept : KeybordEvent(key), repeat(repeat) {}
	public:
		const std::string ToString() const override {
			std::string str = "KeyPressEvent:" + std::to_string(key) + std::to_string(repeat);
			return str;
		}
		Event_Class_Type(KeyPressedEvent)
	private:
		bool repeat;
	};
	class KeyUpEvent : public KeybordEvent {
	public:
		KeyUpEvent(int key) noexcept : KeybordEvent(key) {}
	public:
		const std::string ToString() const override {
			std::string str = "KeyUpEvent:" + std::to_string(key);
			return str;
		}
		Event_Class_Type(KeyUpEvent)
	private:
		bool repeat;
	};
	class MouseMoveEvent : public EventAbstract {
	public:
		MouseMoveEvent(unsigned int x, unsigned int y):x(x),y(y){

		}
		Event_Class_PreType(EventType::Defualt)
	public:
		unsigned int X() const noexcept { return x; }
		unsigned int Y() const noexcept { return y; }
	public:
		const std::string ToString() const override {
			std::string str = "MouseMoveEvent:" + std::to_string(x) + "," + std::to_string(y);
			return str;
		}
		Event_Class_Type(MouseMoveEvent)
	private:
		unsigned int x;
		unsigned int y;
	};
	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button, bool repeat) noexcept :MouseButtonEvent(button), repeat(repeat) {}
	public:
		const std::string ToString() const override {
			std::string str = "MouseButtonPressedEvent:" + std::to_string(button) + std::to_string(repeat);
			return str;
		}
		Event_Class_PreType(EventType::MouseButtonEvent)
		Event_Class_Type(MouseButtonPressedEvent)
	private:
		bool repeat;
	};
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

	
	class PropertyChangedEvent :public EventAbstract{
	public:
		PropertyChangedEvent(const char* propertyName) noexcept:propertyName(propertyName) { sType = EventSpreadType::Direct; }
		Event_Class_Type(PropertyChangedEvent)
	public:
		std::string propertyName;
		void* oldValue;
		void* newValue;
	};
}
