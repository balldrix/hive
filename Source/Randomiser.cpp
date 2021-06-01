#include "Randomiser.h"
#include "Time.h"
#include "pch.h"

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
double Randomiser::GetRandNum(double min, double max)
{
	std::uniform_real_distribution<> dist(min, max); 
	return dist(m_generator);
}

// distribute results between min and max inclusive.  
float Randomiser::GetRandNum(float min, float max)
{
	std::uniform_real_distribution<> dist(min, max);
	return (float)dist(m_generator);
}

// distribute results between min and max inclusive.  
int Randomiser::GetRandNum(int min, int max)
{   
	std::uniform_int_distribution<> dist(min, max); 
    return dist(m_generator);
}