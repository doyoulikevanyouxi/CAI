#include "caipch.h"
#include "TextBox.h"
#include "UI/PaintDeivces/PaintDevice.h"
#include "Events/Events.h"
TextBox::TextBox() noexcept : cursrPostionX(0.0), cursrPostionY(0.0), currentTextLine(0),currentTextColumn(0), totalLines(0)
{
	name = CAISTR(TextBox);

	AddVisualChild(&cursr);
	cursr.SetBackground(0xffc0c0c0);
	cursr.SetPoint(0.0,0.0,2.0,0.0);
	cursr.SetVisible(false);
	cursr.SetLineThickness(10);
	cursAnimation.Target = cursr.GetVisible();
	cursAnimation.From = true;
	cursAnimation.To = false;
	cursAnimation.duration = 0.5;
	cursAnimation.delayDuration = 0.5;
	cursAnimation.Repeat = true;
}

TextBox::~TextBox() noexcept
{
}

void TextBox::SetFontSize(const float& value)
{
	fontSize = value;
	cursr.SetLineThickness(value);
}

void TextBox::OnFocus()
{
	cursr.SetVisible(true);
	storybord.AddAnimation(&cursAnimation);
	storybord.BeginAnimation();
}

void TextBox::OnLostFocus()
{
	cursr.SetVisible(false);
	storybord.StopAnimation();
}

void TextBox::OnTextInput(InputEvent& e)
{
	if (e.GetEventType() != EventSubType::TextInputEvent)
		return;
	TextInputEvent& event = (TextInputEvent&)e;
	text.get() += event.Char();
	//lineTextNumber[currentTextLine]++;
	e.handled = true;
}

void TextBox::OnKeyPress(KeyPressedEvent& e)
{
	storybord.StopAnimation();

	switch (e.KeyCode())
	{
	case KEY_RIGHT:
		currentTextColumn++;
		if (currentTextColumn > lineTextNumber[currentTextLine]) {
			currentTextColumn = 0;
			currentTextLine++;
		}
		break;
    case KEY_LEFT:
		currentTextColumn--;
		if (currentTextColumn == -1) {
			currentTextLine--;
			currentTextColumn = lineTextNumber[currentTextLine];
		}
		break;
    case KEY_DOWN:
		currentTextLine++;
		if (currentTextLine > totalLines)
			currentTextLine = totalLines;
		break;
    case KEY_UP:
		currentTextLine--;
		if (currentTextLine == -1)
			currentTextLine = 0;
		break;
	case KEY_ENTER:
		text.get() += L"\r\n";
		currentTextLine++;
		currentTextColumn = 0;
		lineTextNumber.push_back(0);
		totalLines++;
		break;
	default:
		break;
	}
}

void TextBox::OnKeyUp(KeyUpEvent& e)
{
	storybord.AddAnimation(&cursAnimation);
	storybord.BeginAnimation();
}
