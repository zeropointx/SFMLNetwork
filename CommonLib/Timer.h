#pragma once
#include <ctime>
class Timer
{
public:
	enum State
	{
		STOPPED,
		PAUSED,
		TICKING
	};
	Timer();
	~Timer();
	void start();
	float getCurrentTimeSeconds();
private:
	clock_t startTime;
	State state;
};

