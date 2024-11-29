#pragma once
#include"TimeLine/Duration.h"
//目前动画是建立在cpu计算值再将改变后的值推送到GPU。
//但实际上其实可以对片段着色器做些改动，使其值乘除加减一个变换值，
//把属性的变化计算交由GPU进行

/// <summary>
/// 所有动画的基类
/// 在实现动画时，需要注意帧率，动画效果应该尽量满足至少60帧
/// 当无法满足60帧时，动画将出现卡顿的情况
/// 这里将提供一个统一的方案：
/// 在进行动画前，根据设置，计算60帧下每帧的数据变化范围，或者时间
/// 超出该范围的数据或者时间，将超出的部分延迟到下一帧进行处理，如
/// 果还是超出就继续往后延迟，当超出一定帧仍无法完全处理超出部分，
/// 那么就将剩余超出部分，放入下一帧当中，此操作意味着，该卡顿是无
/// 法避免的。
/// </summary>
class AnimationAbstract
{
public:
	//,初始化数据
	virtual void BeginAnimation() = 0;
	//执行的具体操作
	virtual void Excut() = 0;
public:
	bool Repeat;
	bool Finish;
	Duration duration;
	Duration delayDuration;
};
