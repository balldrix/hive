#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>

class Timer
{
public:
	Timer();
	~Timer();

	UINT64	GetTicks();
	UINT64	GetFrequency();
};

#endif _TIMER_H_