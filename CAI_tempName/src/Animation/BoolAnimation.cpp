#include "caipch.h"
#include "BoolAnimation.h"

void BoolAnimation::BeginAnimation()
{
	//�����ӳٺ�����ʱ��
	originValue = *Target;
	delayDuration.Start();
	duration.Start();
	Finish = false;
	isStart = false;
}

void BoolAnimation::Excut()
{
	//����Ѿ���ʼ������
	if (isStart) {
		goto EXUT;
	}
	//�ӳ�ʱ��δ���������
	if (!delayDuration.TimeUp) {
		delayDuration.Tick();
		return;
	}
	//������ʼִ��
	isStart = true;
	//���ó�ʼֵ
	*Target = From;
	duration.Start();
	return;
EXUT:
	//δִ����
	if (!duration.TimeUp) {
		duration.Tick();
		return;
	}
	//ִ�����
	//����Ϊ�յ�ֵ
	*Target = To;
	isStart = false;
	//�Զ����¿�ʼ
	if (Repeat) {
		//����ʱ��
		delayDuration.ReSet();
		duration.ReSet();
	}
	else {
		Finish = true;
	}
}

void BoolAnimation::Stop()
{
	Finish = true;
	isStart = false;
	*Target = originValue;
}

void BoolAnimation::Pause()
{
}
