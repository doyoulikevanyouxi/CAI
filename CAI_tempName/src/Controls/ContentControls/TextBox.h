#pragma once
#include "Controls/ContentControl.h"
#include "Controls/Shap/Line.h"
#include "Animation/BoolAnimation.h"
class TextBox : public TextBlock
{
public:
	TextBox() noexcept;
	~TextBox() noexcept;
public:
	void SetFontSize(const float& value);
public:
	
	void OnFocus() override;
	void OnLostFocus() override;
protected:
	virtual void OnTextInput(InputEvent& e) override;
	virtual void OnKeyPress(KeyPressedEvent& e) override;
	virtual void OnKeyUp(KeyUpEvent& e) override;
private:
	//光标
	Line cursr;
	//光标的闪烁动画
	BoolAnimation cursAnimation;
	//光标坐标
	float cursrPostionX;
	float cursrPostionY;
	//光标当前指定文字的行列
	unsigned int currentTextLine;
	unsigned int currentTextColumn;
	//总行数
	unsigned int totalLines;

	//每行字的数量
	std::vector<unsigned int> lineTextNumber;
};

