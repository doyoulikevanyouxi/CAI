#pragma once
#include "AnimationAbstract.h"
/// <summary>
/// ���°�
/// ����������ͬһʱ��ִ�еĶ���
/// ͬһʱ��ִ�У�ָ�Ĳ���ͳһ��ʼʱ�䣬����ִ��ʱ�������ڸ�ʱ�䶼Ҫִ��
/// </summary>
class StoryBord
{
public:
	inline bool Empty() { return animations.empty(); }
	inline bool IsBegin() { return isbegin; }
	void AddAnimation(AnimationAbstract* animation);
	void BeginAnimation();
	void Excut();
private:
	std::vector<AnimationAbstract*> animations;
	bool isbegin = false;
};

