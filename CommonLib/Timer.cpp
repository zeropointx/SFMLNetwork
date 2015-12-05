#include "Timer.h"


Timer::Timer()
{
	state = STOPPED;
}


Timer::~Timer()
{
}
void Timer::start()
{
	startTime = clock();
}
float Timer::getCurrentTimeSeconds()
{
	return float(clock() - startTime) / CLOCKS_PER_SEC;
}