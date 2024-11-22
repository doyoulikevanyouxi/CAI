#include "caipch.h"
#include "TextInpreter.h"

void TextInpreter::Init()
{
	xmglInpreter = std::make_shared<XMGL::XMLInterpreter>();
}
