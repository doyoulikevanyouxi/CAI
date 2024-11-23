#pragma once
#include "../EControl.h"
#include <UI/Character.h>
class TextBlock : public Control
{
public:
	
public:
	TextBlock() noexcept;
	TextBlock(const std::wstring& str) noexcept;
	virtual ~TextBlock() noexcept;
public:
	void setText(const std::wstring& str) noexcept;
public:
	virtual void Render() noexcept override;
public:
	DependencyProperty<std::wstring> text{ "Text" };
	DependencyProperty<unsigned int> fontSize{ "FontSize" };
	DependencyProperty<Draw::Color> fontBrush{ "FontBrush" };
	DependencyProperty<TextOverRangeOperator> overranging{ "Overranging" };
};

