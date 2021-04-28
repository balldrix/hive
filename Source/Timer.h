#pragma once

#include "pch.h"

class Timer
{
public:
	Timer();
	~Timer();

	float	GetTicks(); // get cpu time in ticks
	float	GetFrequency(); // get cpu frequency
};