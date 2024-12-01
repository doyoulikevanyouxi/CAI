#include "caipch.h"
#include "TextBlock.h"
#include "UI/PaintDeivces/PaintDevice.h"
#include "Datas/ControlStyle.h"
#include "UI/Character.h"
TextBlock::TextBlock() noexcept
{
	fontSize.set(12);
	fontBrush.set(Draw::Color(Draw::Color::BLACK));
	overranging.set(TextOverRangeOperator::Default);
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

void TextBlock::Render() noexcept
{
	UIElement::Render();
	if (text.get().empty())
		return;
	pDevice->DrawText(text.get(), vData.ContentSize(), { fontSize.get(),fontBrush.get(),overranging.get() });
}
