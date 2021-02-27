// Timer.h
// Christopher Ball 2019-2021
// gets cpu time and frequency for delta time management

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