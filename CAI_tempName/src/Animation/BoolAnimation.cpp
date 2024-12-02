#include "caipch.h"
#include "BoolAnimation.h"

void BoolAnimation::BeginAnimation()
{
	//启动延迟和区间时间
	originValue = *Target;
	delayDuration.Start();
	duration.Start();
	Finish = false;
	isStart = false;
}

void BoolAnimation::Excut()
{
	//如果已经开始，跳至
	if (isStart) {
		goto EXUT;
	}
	//延迟时间未到，不向后
	if (!delayDuration.TimeUp) {
		delayDuration.Tick();
		return;
	}
	//真正开始执行
	isStart = true;
	//设置初始值
	*Target = From;
	duration.Start();
	return;
EXUT:
	//未执行玩
	if (!duration.TimeUp) {
		duration.Tick();
		return;
	}
	//执行完毕
	//设置为终点值
	*Target = To;
	isStart = false;
	//自动重新开始
	if (Repeat) {
		//重置时间
		delayDuration.ReSet();
		duration.ReSet();
	}
	else {
		Finish = true;
	}
}

void BoolAnimation::Stop()
{
	Finish = true;
	isStart = false;
	*Target = originValue;
}

void BoolAnimation::Pause()
{
}
