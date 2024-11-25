#pragma once
#include"TimeLine/Duration.h"
class AnimationAbstract
{
public:
	virtual void BeginAnimation() = 0;
	virtual void Excut() = 0;
public:
	bool Repeat;
	bool Finish;
protected:
	Duration duration;
	Duration delayDuration;
};

