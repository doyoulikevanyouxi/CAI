#pragma once
#include"EventAbstract.h"
class InputEvent : public EventAbstract {
public:
	Event_Class_PreType(EventType::InputEvent)
};

class KeybordEvent :public InputEvent {
public:
	inline int KeyCode() const noexcept { return key; }
protected:
	KeybordEvent(int key) noexcept : key(key) {}
protected:
	int key;
};

/// <summary>
	/// 键盘按下事件
	/// </summary>
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

/// <summary>
/// 键盘弹起事件
/// </summary>
class KeyUpEvent : public KeybordEvent {
public:
	KeyUpEvent(int key) noexcept : KeybordEvent(key) {}
public:
	const std::string ToString() const override {
		std::string str = "KeyUpEvent:" + std::to_string(key);
		return str;
	}
	Event_Class_Type(KeyUpEvent)
};

/// <summary>
/// 文本输入事件
/// </summary>
class TextInputEvent :public InputEvent {
public:
	TextInputEvent(unsigned int charUnicode) noexcept :unicode(charUnicode) {}
	const std::string ToString() const override {
		std::string str = "TextInputEvent:" + unicode;
		return str;
	}
	inline unsigned int Char() { return unicode; }
	Event_Class_Type(TextInputEvent)
protected:
	unsigned int unicode;
};
