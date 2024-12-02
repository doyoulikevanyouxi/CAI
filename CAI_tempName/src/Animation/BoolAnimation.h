#pragma once
#include "AnimationAbstract.h"
/// <summary>
/// bool类型动画
/// </summary>
class BoolAnimation : public AnimationAbstract
{
public:
	//起始值
	bool From;
	//目标值
	bool To;
	//目标对象
	bool* Target;
	// 通过 AnimationAbstract 继承
	void BeginAnimation() override;
	void Excut();
private:
	//是否已经开始执行
	bool isStart;
	bool originValue;
	// 通过 AnimationAbstract 继承
	void Stop() override;
	void Pause() override;
};

