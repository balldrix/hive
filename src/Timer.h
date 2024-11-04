#pragma once

class Timer
{
public:
	Timer() {};
	~Timer() {};

	static float GetTicks();
	static float GetFrequency();
};