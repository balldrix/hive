// Randomiser.h
// Christopher Ball 2019
// Utility class with template to randomise numbers

#ifndef _RANDOMISER_H_
#define _RANDOMISER_H_

#include "pch.h"

class Randomiser
{
public:
	Randomiser();
	Randomiser(int seed); // constructor that passes a user defined seed
	~Randomiser();

	// get random number
	static double GetRandNum(double min, double max);
	static int GetRandNum(int min, int max);
};

#endif _RANDOMISER_H_

