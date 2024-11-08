#include "caipch.h"
#include "TextBox.h"
#include "UI/PaintDevice.h"
TextBox::TextBox() noexcept
{
	name = CAISTR(TextBox);
	fontSize.set(12);
}

TextBox::~TextBox() noexcept
{
}

void TextBox::render() noexcept
{
	UIElement::render();
	if (text.empty())
		return;
	pDevice->DrawText(text, style->styleData().AreaSize());
}

void TextBox::OnInput(CAITF::InputEvent& e)
{
	if (e.GetEventType() != CAITF::EventSubType::TextInputEvent)
		return;
	CAITF::TextInputEvent& event = (CAITF::TextInputEvent&)e;
	text += event.Char();
	e.handled = true;
}
