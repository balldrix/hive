#include "Randomiser.h"
#include "Time.h"
#include "pch.h"

Randomiser::Randomiser()
{
	m_generator = std::mt19937((int)time(NULL));
}

Randomiser::~Randomiser()
{

}

Randomiser* Randomiser::Instance()
{
	static Randomiser instance;
	return &instance;
}

double Randomiser::GetRandNum(double min, double max)
{
	std::uniform_real_distribution<> dist(min, max); // distribute results between min and max inclusive.  
	return dist(m_generator);
}

int Randomiser::GetRandNum(int min, int max)
{   
	std::uniform_int_distribution<> dist(min, max); // distribute results between min and max inclusive.  
    return dist(m_generator);
}
