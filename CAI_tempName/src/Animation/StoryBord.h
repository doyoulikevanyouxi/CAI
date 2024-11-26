#pragma once
#include "AnimationAbstract.h"
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

