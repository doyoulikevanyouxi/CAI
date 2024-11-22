#pragma once
#include "Object.h"
#include "Events/Events.h"
class Element : public Object
{
protected:
	//virtual void OnResize() = 0;
	//virtual void OnRender();
	//virtual void OnMouseOver();
	//virtual void OnMouseLeftButtonPress();
	//virtual void OnMouseLeftButtonUp();
	virtual void OnInput(InputEvent& e) = 0;
	virtual void OnMouseLeave(MouseLeaveEvent& e) = 0;
	virtual void OnMouseEnter(MouseEnterEvent& e) = 0;
	virtual void OnPreMouseOver(PreMouseOverEvent& e) = 0;
	virtual void OnMouseOver(MouseOverEvent& e) = 0;
	/*virtual void OnMouseIn();
	virtual void OnMouseLeft();*/
	virtual void OnEvent(EventAbstract& e) = 0;
	virtual void RaiseEvent(EventAbstract& e) = 0;
public:
	void* dataContext;
	bool focus = false;
	bool isMouseOver = false;
	bool isMouseDirectOver = false;
	bool isMouseEnter = false;
};

