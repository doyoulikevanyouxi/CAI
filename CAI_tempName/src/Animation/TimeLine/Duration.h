#pragma once
#include <chrono>
//ʱ����
class Duration
{
public:
	Duration() = default;
	Duration(double time);
	~Duration() = default;
public:
	bool TimeUp;
public:
	//��ʼ��ʱ��
	void Start();
	//������ʱ��
	void Tick();
	//����
	void ReSet();
	//�趨��ʱ����
	double timeSpan;

private:
	std::chrono::steady_clock::time_point startTimePoint;
};

