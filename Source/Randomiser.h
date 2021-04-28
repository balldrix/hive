#pragma once

#include "pch.h"

class Randomiser
{
public:
	~Randomiser();

	static Randomiser* Instance();
	
	double GetRandNum(double min, double max);
	float GetRandNum(float min, float max);
	int GetRandNum(int min, int max);

	std::mt19937 m_generator;

private:
	Randomiser();
};