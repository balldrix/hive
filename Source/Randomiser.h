// Randomiser.h
// Christopher Ball 2019-2020
// Utility class with template to randomise numbers

#ifndef _RANDOMISER_H_
#define _RANDOMISER_H_

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

#endif _RANDOMISER_H_

