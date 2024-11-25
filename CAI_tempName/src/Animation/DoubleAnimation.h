#pragma once
#include "AnimationAbstract.h"

class DoubleAnimation : public AnimationAbstract
{
public:
	double From;
	double To;
private:
	double speed;
};

