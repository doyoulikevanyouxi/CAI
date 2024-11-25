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
		if (hasSetContent) {
			return;
		}
		if (selfCreatEle == nullptr) {
			selfCreatEle = new TextBlock();
			AddVisualChild(selfCreatEle);
		}
		selfCreatEle->setText(str);
		content.set(selfCreatEle);
		hasSetContent = true;
	}
	void setContent(UIElement* elem) {
		if (hasSetContent) {
			return;
		}
		content.set(elem);
		AddVisualChild(elem);
		elem->SetParent(this);
		hasSetContent = true;
	}
public:
	DependencyProperty<UIElement*> content{ "Content" };
private:
	bool hasSetContent = false;
	TextBlock* selfCreatEle;
};

