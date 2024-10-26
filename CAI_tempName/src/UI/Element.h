#pragma once
#include "Object.h"
#include "Events/Events.h"

class Element : public Object
{
public:
	//void registEventCallBack(std::function<void(CAITF::EventAbstract)> ,std::function<void(CAITF::EventAbstract)>);
protected:
	//virtual void OnResize() = 0;
	//virtual void OnRender();
	//virtual void OnMouseOver();
	//virtual void OnMouseLeftButtonPress();
	//virtual void OnMouseLeftButtonUp();
	virtual void OnMouseOver( CAITF::MouseMoveEvent& e) =0;
	virtual void OnEvent( CAITF::EventAbstract& e) = 0;
protected:
	CAITF::EventDispatcher eventDispatcher;
};

