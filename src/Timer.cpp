#include "Timer.h"

#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

float Timer::GetTicks()
{
	LARGE_INTEGER ticks;

	if (!QueryPerformanceCounter(&ticks))
	{
		ticks.QuadPart = timeGetTime();
	}
	return (float)ticks.QuadPart;
}

float Timer::GetFrequency()
{
	LARGE_INTEGER frequency;

	if (!QueryPerformanceFrequency(&frequency))
	{
		frequency.QuadPart = 1000;
	}
	return 1 / (float)frequency.QuadPart;
}