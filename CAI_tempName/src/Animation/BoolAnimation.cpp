#include "caipch.h"
#include "BoolAnimation.h"

void BoolAnimation::BeginAnimation()
{
	//�����ӳٺ�����ʱ��
	delayDuration.Start();
	duration.Start();
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
