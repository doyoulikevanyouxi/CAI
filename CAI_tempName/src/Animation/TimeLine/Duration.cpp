#include "caipch.h"
#include "Duration.h"

void Duration::Start()
{
	startTimePoint = std::chrono::high_resolution_clock::now();
}

void Duration::Excu()
{
	auto tNow = std::chrono::high_resolution_clock::now();
	double t = (tNow - startTimePoint).count() / 1000.f / 1000.f / 1000.f;
	if (t >= timeSpan) {
		TimeUp = true;
	}
}

void Duration::ReSet()
{
	startTimePoint = std::chrono::high_resolution_clock::now();
	TimeUp = false;
}
