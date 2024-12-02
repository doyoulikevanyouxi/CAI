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
	//���
	Line cursr;
	//������˸����
	BoolAnimation cursAnimation;
	//�������
	float cursrPostionX;
	float cursrPostionY;
	//��굱ǰָ�����ֵ�����
	unsigned int currentTextLine;
	unsigned int currentTextColumn;
	//������
	unsigned int totalLines;

	//ÿ���ֵ�����
	std::vector<unsigned int> lineTextNumber;
};

