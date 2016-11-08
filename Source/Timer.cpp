#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

float	
Timer::GetTicks()
{
	LARGE_INTEGER ticks;

	if (!QueryPerformanceCounter(&ticks)) // query cpu time
	{
		ticks.QuadPart = timeGetTime(); // if Query fails set to standard clock time
	}
	return (float)ticks.QuadPart; // return time
}

float
Timer::GetFrequency()
{
	LARGE_INTEGER frequency;

	if (!QueryPerformanceFrequency(&frequency)) // query cpu ticks per second
	{
		frequency.QuadPart = 1000; // if query fails set to 1000 ticks
	}
	return 1 / (float)frequency.QuadPart; // return ticks as a fraction of a second
}