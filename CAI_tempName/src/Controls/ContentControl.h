#pragma once
#include"EControl.h"
#include"Datas/ControlStyle.h"
#include"ContentControls/TextBlock.h"
class ContentControl : public Control
{
public:
	ContentControl()	noexcept :selfCreatEle(nullptr) {}
	virtual ~ContentControl() noexcept {
		if (selfCreatEle != nullptr)
			delete selfCreatEle;
	}
public:
	void setContent(const std::wstring& str) {
		if (selfCreatEle == nullptr) {
			selfCreatEle = new TextBlock();
			style->addChildToVisual(*selfCreatEle);
		}
		selfCreatEle->setText(str);
		content.set(selfCreatEle);
	}
	void setContent(UIElement& elem) {
		content.set(&elem);
		style->addChildToVisual(elem);
		elem.SetParent(this);
	}
public:
	DependencyProperty<Object*> content{ "Content" };
private:
	TextBlock* selfCreatEle;
};

