#pragma once
#include "AnimationAbstract.h"
using animationFun = void(AnimationAbstract::*)(void);
class StoryBord
{
public:
	void AddAnimation(AnimationAbstract*& animation);
	void BeginAnimation();
	void Excut();
private:
	std::vector<AnimationAbstract*> animations;
};

