#pragma once
#include <string>
namespace CAITF {
	enum	 EventType {
		KeybordEvent = 1<<2,
		MouseButtonEvent = 1<<3,
		ValueChangedEvent = 1 << 4,
		Defualt 
	};

	enum class EventSubType {
		None = 0,
		WindowResizeEvent,
		KeyPressedEvent, KeyUpEvent,
		MouseMoveEvent, MouseButtonPressedEvent, MouseButtonUpEvent,
		PropertyChangedEvent,
		Defualt
	};

	enum class EventSpreadType {
		Tunnel,
		Bubble,
		Direct
	};

#define Event_Class_Type(x) static  EventSubType static_EventType() noexcept {return EventSubType::##x;}\
						 virtual EventSubType GetEventType() const noexcept override{ return static_EventType();}\
						 virtual const char* GetName() const noexcept override{return #x;}
#define Event_Class_PreType(x) virtual EventType GetEventPreType() const noexcept override {return x;}
	class EventAbstract
	{
	public:
		virtual EventSubType GetEventType() const noexcept = 0;
		virtual const char* GetName() const noexcept = 0;
		virtual const std::string ToString() const{ return GetName(); }
		virtual EventType GetEventPreType() const noexcept = 0;
	public:
		EventSpreadType  sType = EventSpreadType::Tunnel;
		void* source = nullptr;
		void* target = nullptr;
		bool handled = false;
	};

	class EventDispatcher {

	public:
		EventDispatcher(EventType filt = EventType::Defualt, EventSubType subFilt = EventSubType::Defualt) noexcept :filt(filt), subFilt(subFilt){}
		EventType filt;
		EventSubType subFilt;
		bool filter(EventAbstract& e) {
			if (e.handled)
				return true;
		/*	if (!( e.GetEventPreType() & filt))
				return true;
			else
				return &e;*/
			return false;
		}

	};

}
