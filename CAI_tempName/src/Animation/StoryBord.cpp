#include "caipch.h"
#include "StoryBord.h"

void StoryBord::AddAnimation(AnimationAbstract* animation)
{
	animations.push_back(animation);
}

void StoryBord::StopAnimation()
{
	for (auto& animation : animations) {
		animation->Stop();
	}
	isbegin = false;
	animations.clear();
}

void StoryBord::BeginAnimation()
{
	for (auto& animation : animations) {
		animation->BeginAnimation();
	}
	isbegin = true;
}

void StoryBord::Excut()
{
	if (animations.empty()) {
		isbegin = false;
		return;
	}
	for (int i = 0; i < animations.size(); ++i) {
		animations[i]->Excut();
		if (animations[i]->Finish)
			animations.erase(animations.begin() + i);
	}
}
