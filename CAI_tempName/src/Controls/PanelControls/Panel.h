#pragma once
#include "../EControl.h"
#include"Mathmatics/Math.hpp"
#include "Datas/VisualCollection.h"
/// <summary>
/// Panel�ؼ�����Ϊ�������ɵĿؼ������Ű�ʹ�С�趨
/// ���̳���Control������Ϊ��������������û��̫�����Ⱦ����
/// ���ֿؼ���ʵ��������һ���任����ʹ�øÿؼ��µ���Ԫ�ظ��ݱ任������б任
/// ������������ž�����ʱ������ӽ�������Ҫ���������Ԫ�صĴ�С��λ��
/// </summary>
class Panel : public Control
{
public:
	Panel() noexcept;
	virtual ~Panel();
public:
	virtual void AddChild(UIElement* child);

protected:
	VisualCollection childs;
protected:
	Math::mat4 transMatrix;
	/// <summary>
	/// x����
	/// </summary>
	float xIncrement;
	/// <summary>
	/// y����
	/// </summary>
	float yIncrement;
};

