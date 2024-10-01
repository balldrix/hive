#pragma once

#include "pch.h"

class Timer
{
public:
	Timer();
	~Timer();

	float	GetTicks();
	float	GetFrequency();
};