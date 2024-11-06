#pragma once

class Timer
{
public:
	Timer() {};
	~Timer() {};

	unsigned __int64 GetTicks() const;
	unsigned __int64 GetFrequency() const;
};