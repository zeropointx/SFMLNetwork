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
	clock_t end = clock();
	return float(end - startTime) / CLOCKS_PER_SEC;
}