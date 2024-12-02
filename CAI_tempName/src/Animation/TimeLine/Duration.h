#pragma once
#include <chrono>
//时间间隔
class Duration
{
public:
	Duration() = default;
	Duration(double time);
	~Duration() = default;
public:
	bool TimeUp;
public:
	//开始记时间
	void Start();
	//经过的时间
	void Tick();
	//重置
	void ReSet();
	//设定的时间间隔
	double timeSpan;

private:
	std::chrono::steady_clock::time_point startTimePoint;
};

