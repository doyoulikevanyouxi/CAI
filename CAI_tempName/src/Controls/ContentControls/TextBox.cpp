#include "caipch.h"
#include "TextBox.h"
#include "UI/PaintDeivces/PaintDevice.h"
#include "Events/Events.h"
TextBox::TextBox() noexcept
{
	name = CAISTR(TextBox);
}

TextBox::~TextBox() noexcept
{
}

void TextBox::OnTextInput(InputEvent& e)
{
	if (e.GetEventType() != EventSubType::TextInputEvent)
		return;
	TextInputEvent& event = (TextInputEvent&)e;
	text.get() += event.Char();
	e.handled = true;
}
