#pragma once
#include "UIElement.h"
#include "UIElementCollection.h"
/// <summary>
/// Panel�ؼ�����Ϊ�������ɵĿؼ������Ű�ʹ�С�趨��ǰ�����ӿؼ�û��ǿ�������Լ���λ�ú�����
/// ���̳���Control������Ϊ��������������û��̫�����Ⱦ����
/// </summary>
class Panel : public UIElement
{
public:
	Panel() noexcept;
	virtual ~Panel();
protected:
	UIElementCollection childs;
};

