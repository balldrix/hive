#include "Timer.h"

Timer::Timer()
{

}

Timer::~Timer()
{

}

UINT64	
Timer::GetTicks()
{
	UINT64 ticks;

	if (!QueryPerformanceCounter((LARGE_INTEGER*)&ticks))
	{
		ticks = (UINT64)timeGetTime;
	}
	return ticks;
}

UINT64
Timer::GetFrequency()
{
	UINT64 frequency;

	if (!QueryPerformanceFrequency((LARGE_INTEGER*)&frequency))
	{
		frequency = 1000;
	}
	return frequency;
}