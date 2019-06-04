#include "Randomiser.h"
#include "Time.h"
#include "pch.h"

Randomiser::Randomiser()
{
	srand((int)time(NULL));
}

Randomiser::~Randomiser()
{

}

Randomiser::Randomiser(int seed)
{
	srand(seed);
}

double Randomiser::GetRandNum(double min, double max)
{
	std::random_device rd;   // non-deterministic generator  
	std::mt19937 gen(rd());  // to seed mersenne twister.  
	std::uniform_real_distribution<> dist(min, max); // distribute results between 1 and 6 inclusive.  
	return dist(rd);
}

int Randomiser::GetRandNum(int min, int max)
{
	std::random_device rd;   // non-deterministic generator  
	std::mt19937 gen(rd());  // to seed mersenne twister.  
	std::uniform_int_distribution<> dist(min, max); // distribute results between 1 and 6 inclusive.  
    return dist(rd);
}
