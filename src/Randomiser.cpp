#include "Randomiser.h"

#include <ctime>

Randomiser::Randomiser()
{
	m_generator = std::mt19937((int)time(nullptr));
}

Randomiser::~Randomiser()
{

}

Randomiser* Randomiser::Instance()
{
	static Randomiser instance;
	return &instance;
}

// distribute results between min and max inclusive.
double Randomiser::GetRandNumUniform(double min, double max)
{
	std::uniform_real_distribution<> dist(min, max); 
	return dist(m_generator);
}

// distribute results between min and max inclusive.
float Randomiser::GetRandNumUniform(float min, float max)
{
	std::uniform_real_distribution<> dist(min, max);
	return (float)dist(m_generator);
}

// distribute results between min and max inclusive.
int Randomiser::GetRandNumUniform(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);
	return dist(m_generator);
}

float Randomiser::GetRandNumNormal(float min, float max)
{
	std::normal_distribution<> dist(min, max);
	return dist(m_generator);
}
