// Timer.h
// Christopher Ball
// gets cpu time and frequency for delta time management

#ifndef _TIMER_H_
#define _TIMER_H_

#include "pch.h"

class Timer
{
public:
	Timer();
	~Timer();

	float	GetTicks(); // get cpu time in ticks
	float	GetFrequency(); // get cpu frequency
};

#endif _TIMER_H_