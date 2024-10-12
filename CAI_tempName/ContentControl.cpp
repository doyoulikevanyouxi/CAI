#include "ContentControl.h"
#include"UIElement.h"
#include<typeinfo>
#include"ControlStyle.h"

ContentControl::ContentControl() noexcept
{
}

ContentControl::~ContentControl() noexcept
{
}

void ContentControl::setContent(Object& elem)
{

	try {
		UIElement& uElem = dynamic_cast<UIElement&>(elem);
		content.set(&elem);
		style->addChildToVisual(uElem);
		uElem.setParent(this);
	}
	catch (std::bad_cast& e) {
		int a = 10;
	}

}
