#pragma once
#include "Panel.h"
/// <summary>
/// �����ò������� ˮƽ����
/// </summary>
class TedPanel : public Panel
{
public:
	TedPanel()noexcept;
	~TedPanel() noexcept;
protected:
	void measure(const Size& size) noexcept override ;
public:
	void AddChild(UIElement* child);
	void init(Size& size);
};

