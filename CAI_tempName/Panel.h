#pragma once
#include "UIElement.h"
#include "Collection.h"
#include"Math.hpp"
/// <summary>
/// Panel�ؼ�����Ϊ�������ɵĿؼ������Ű�ʹ�С�趨
/// ���̳���Control������Ϊ��������������û��̫�����Ⱦ����
/// ���ֿؼ���ʵ��������һ���任����ʹ�øÿؼ��µ���Ԫ�ظ��ݱ任������б任
/// ������������ž�����ʱ������ӽ�������Ҫ���������Ԫ�صĴ�С��λ��
/// </summary>
class Panel : public UIElement
{
public:
	Panel() noexcept;
	virtual ~Panel();
public:
	virtual void addChild(UIElement& child);

protected:
	UIElementCollection childs;
protected:
	Math::TransMatrix transMatrix;
	/// <summary>
	/// x����
	/// </summary>
	float xIncrement;
	/// <summary>
	/// y����
	/// </summary>
	float yIncrement;
};

