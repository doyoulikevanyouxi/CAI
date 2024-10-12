#pragma once
#include "Panel.h"
/// <summary>
/// 测试用布局容器 水平布局 换行和不换行，拉伸和不拉伸
/// 布局控件需要重写void measure(const Size& size) 测量函数，
/// 以便为子元素提供不同的变换矩阵
/// </summary>
class TedPanel : public Panel
{
public:
	TedPanel()noexcept;
	~TedPanel() noexcept;
protected:
	virtual void aeasure(const Size& size) noexcept override;
public:
	bool wrap = true;
};

