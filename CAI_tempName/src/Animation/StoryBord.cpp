#include "caipch.h"
#include "StoryBord.h"

void StoryBord::AddAnimation(AnimationAbstract*& animation)
{
	animations.push_back(animation);
}

void StoryBord::BeginAnimation()
{
	for (auto& animation : animations) {
		animation->BeginAnimation();
	}
}

void StoryBord::Excut()
{
	for (int i = 0; i < animations.size(); ++i) {
		animations[i]->Excut();
		if (animations[i]->Finish)
			animations.erase(animations.begin() + i);
	}
}
