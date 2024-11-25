#pragma once
#include <chrono>
//Ê±¼ä¼ä¸ô
class Duration
{
public:
	bool TimeUp;
public:
	void Start();
	void Excu();
	void ReSet();
protected:
	
private:
	double timeSpan;
	std::chrono::steady_clock::time_point startTimePoint;
};

