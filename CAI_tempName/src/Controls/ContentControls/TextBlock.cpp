#include "caipch.h"
#include "TextBlock.h"
#include "UI/PaintDevice.h"
#include "Datas/ControlStyle.h"
TextBlock::TextBlock() noexcept
{
}
TextBlock::TextBlock(const std::wstring& str) noexcept
{
	text.set(str);
}

TextBlock::~TextBlock() noexcept
{
}

void TextBlock::setText(const std::wstring& str) noexcept
{
	text.set(str);
}

void TextBlock::render() noexcept
{
	UIElement::render();
	if (text.get().empty())
		return;
	pDevice->DrawText(text.get(), style->styleData().AreaSize());
}
