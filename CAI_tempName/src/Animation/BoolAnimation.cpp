#include "caipch.h"
#include "BoolAnimation.h"

void BoolAnimation::BeginAnimation()
{
	delayDuration.Start();
	duration.Start();
}

void BoolAnimation::Excut()
{
	if (isStart) {
		goto EXUT;
	}
	if (!delayDuration.TimeUp) {
		delayDuration.Excu();
		return;
	}
	isStart = true;
	*Target = From;
	duration.Start();
	return;
	EXUT:
	if (!duration.TimeUp) {
		duration.Excu();
		return;
	}
	*Target = To;
	isStart = false;
	if (Repeat) {
		delayDuration.ReSet();
		duration.ReSet();
	}
	else {
		Finish = true;
	}
}
