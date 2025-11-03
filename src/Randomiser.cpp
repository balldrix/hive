#include "Randomiser.h"

#include <ctime>
#include <random>

std::mt19937 Randomiser::s_generator = std::mt19937((int)time(nullptr));

// distribute results between min and max inclusive.
double Randomiser::GetRandNumUniform(double min, double max)
{
	std::uniform_real_distribution<> dist(min, max); 
	return dist(s_generator);
}

// distribute results between min and max inclusive.
float Randomiser::GetRandNumUniform(float min, float max)
{
	std::uniform_real_distribution<> dist(min, max);
	return (float)dist(s_generator);
}

// distribute results between min and max inclusive.
int Randomiser::GetRandNumUniform(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(s_generator);
}

float Randomiser::GetRandNumNormal(float min, float max)
{
	std::normal_distribution<> dist(min, max);
	return dist(s_generator);
}
