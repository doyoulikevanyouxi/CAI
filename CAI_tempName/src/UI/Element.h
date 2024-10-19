#pragma once
#include "Object.h"
#include "Events/Events.h"

class Element : public Object
{
public:
	//void registEventCallBack(std::function<void(CAI::EventAbstract)> ,std::function<void(CAI::EventAbstract)>);
protected:
	//virtual void OnResize() = 0;
	//virtual void OnRender();
	//virtual void OnMouseOver();
	//virtual void OnMouseLeftButtonPress();
	//virtual void OnMouseLeftButtonUp();
	virtual void OnMouseOver( CAI::MouseMoveEvent& e) =0;
	virtual void OnEvent( CAI::EventAbstract& e) = 0;
protected:
	CAI::EventDispatcher eventDispatcher;
};

