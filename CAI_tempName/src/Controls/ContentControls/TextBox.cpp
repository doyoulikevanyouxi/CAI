#include "caipch.h"
#include "TextBox.h"
#include "UI/PaintDevice.h"
TextBox::TextBox() noexcept
{
	name = CAISTR(TextBox);
}

TextBox::~TextBox() noexcept
{
}

void TextBox::OnInput(CAITF::InputEvent& e)
{
	if (e.GetEventType() != CAITF::EventSubType::TextInputEvent)
		return;
	CAITF::TextInputEvent& event = (CAITF::TextInputEvent&)e;
	text.get() += event.Char();
	e.handled = true;
}
