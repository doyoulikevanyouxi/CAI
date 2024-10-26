#pragma once
namespace CAITF {
	enum	 EventType {
		KeybordEvent,
		MouseButtonEvent,
		Defualt
	};

	enum class EventSubType {
		WindowResizeEvent,
		KeyPressedEvent, KeyUpEvent,
		MouseMoveEvent, MouseButtonPressedEvent, MouseButtonUpEvent
	};

#define Event_Class_Type(x) static  EventSubType static_EventType() noexcept {return EventSubType::##x;}\
						 virtual EventSubType GetEventType() const noexcept override{ return static_EventType();}\
						 virtual const char* GetName() const noexcept override{return #x;}

	class EventAbstract
	{
	public:
		virtual EventSubType GetEventType() const noexcept = 0;
		virtual const char* GetName() const noexcept = 0;
		virtual const std::string ToString() const{ return GetName(); }
	public:
		bool handled = false;
	};

	class EventDispatcher {


	};

}
