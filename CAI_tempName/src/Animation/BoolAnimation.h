#pragma once
#include "AnimationAbstract.h"
class BoolAnimation : public AnimationAbstract
{
public:
	bool From;
	bool To;
	bool* Target;
	// ͨ�� AnimationAbstract �̳�
	void BeginAnimation() override;
	void Excut();
private:
	bool isStart;
};

