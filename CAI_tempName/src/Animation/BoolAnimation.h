#pragma once
#include "AnimationAbstract.h"
/// <summary>
/// bool���Ͷ���
/// </summary>
class BoolAnimation : public AnimationAbstract
{
public:
	//��ʼֵ
	bool From;
	//Ŀ��ֵ
	bool To;
	//Ŀ�����
	bool* Target;
	// ͨ�� AnimationAbstract �̳�
	void BeginAnimation() override;
	void Excut();
private:
	//�Ƿ��Ѿ���ʼִ��
	bool isStart;
	bool originValue;
	// ͨ�� AnimationAbstract �̳�
	void Stop() override;
	void Pause() override;
};

