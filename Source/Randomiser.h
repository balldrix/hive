// Randomiser.h
// Christopher Ball 2017
// Utility class with template to randomise numbers

#ifndef _RANDOMISER_H_
#define _RANDOMISER_H_

class Randomiser
{
public:
	Randomiser();
	Randomiser(int seed); // constructor that passes a user defined seed
	~Randomiser();

	// template function to get a random number between min and max values
	template<typename T>
	static T GetRandNum(T min, T max);
};

template<typename T>
T
Randomiser::GetRandNum(T min, T max)
{
	T range = max - min + 1; // get range between min and max
	return (rand() % range) + min; // return random number within range
}

#endif _RANDOMISER_H_

