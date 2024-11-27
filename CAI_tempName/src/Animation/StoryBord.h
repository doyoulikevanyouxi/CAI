#pragma once
#include "AnimationAbstract.h"
/// <summary>
/// 故事板
/// 包含了所有同一时间执行的动画
/// 同一时间执行，指的不是统一开始时间，而是执行时各动画在该时间都要执行
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

