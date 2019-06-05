// Randomiser.h
// Christopher Ball 2019
// Utility class with template to randomise numbers

#ifndef _RANDOMISER_H_
#define _RANDOMISER_H_

#include "pch.h"

class Randomiser
{
public:
	~Randomiser();

	static Randomiser* Instance();
	// get random number
	double GetRandNum(double min, double max);
	int GetRandNum(int min, int max);

	std::mt19937 m_generator;
private:
	Randomiser();
};

#endif _RANDOMISER_H_

