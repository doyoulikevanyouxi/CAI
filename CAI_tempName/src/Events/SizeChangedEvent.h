#pragma once
#include "EventAbstract.h"
#include "Datas/Coordinate.h"
class SizeChangedEvent : public EventAbstract
{
public:
	SizeChangedEvent(const Size& size) : newSize(size) {}
	Event_Class_PreType(EventType::SizeChangedEvent)
private:
	Size newSize;
};

class ControlSizeChangedEvent : public SizeChangedEvent {
public:
	ControlSizeChangedEvent(const Size& size) : SizeChangedEvent(size) {}
	const std::string ToString() const override {
		std::string str = "ControlSizeChangedEvent";
		return str;
	}
	Event_Class_Type(ControlSizeChangedEvent)

};

