#pragma once
#include "Controls/ContentControl.h"
class TextBox : public ContentControl
{
public:
	TextBox() noexcept;
	~TextBox() noexcept;
public:
	virtual void render() noexcept override;
protected:
	virtual void OnInput(CAITF::InputEvent& e) override;
private:
	std::wstring text;
};

