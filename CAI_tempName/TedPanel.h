#pragma once
#include "Panel.h"
/// <summary>
/// �����ò������� ˮƽ���� ���кͲ����У�����Ͳ�����
/// ���ֿؼ���Ҫ��дvoid measure(const Size& size) ����������
/// �Ա�Ϊ��Ԫ���ṩ��ͬ�ı任����
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

