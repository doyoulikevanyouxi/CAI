#pragma once
#include "Controls/ContentControl.h"
class TextBox : public TextBlock
{
public:
	TextBox() noexcept;
	~TextBox() noexcept;
protected:
	virtual void OnInput(InputEvent& e) override;
};

