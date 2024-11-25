#pragma once
#include "AnimationAbstract.h"
class BoolAnimation : public AnimationAbstract
{
public:
	bool From;
	bool To;
	bool AutoRepeat;
	bool* Target;
	// Í¨¹ý AnimationAbstract ¼Ì³Ð
	void BeginAnimation() override;
	void Excut();
private:
	bool isStart;
};

