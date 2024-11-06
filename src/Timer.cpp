#include "Timer.h"

#include <windows.h>

unsigned __int64 Timer::GetTicks() const
{
    unsigned __int64 ticks = 0;

    if(!QueryPerformanceCounter((LARGE_INTEGER*) &ticks))
    {
        // Fallback to timeGetTime in milliseconds if QPC fails
        ticks = (__int64) timeGetTime();
    }

    return ticks;
}

unsigned __int64 Timer::GetFrequency() const
{
    unsigned __int64 frequency = 0;

    if(!QueryPerformanceFrequency((LARGE_INTEGER*) &frequency))
    {
        // Fallback frequency for timeGetTime
        frequency = 1000;
    }

    return frequency;
}