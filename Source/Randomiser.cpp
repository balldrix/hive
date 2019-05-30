#include "Randomiser.h"
#include "Time.h"
#include "stdlib.h"

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
	static std::default_random_engine engine;
	static std::uniform_real_distribution<> distribution(min, max);
	return distribution(engine);
}

int Randomiser::GetRandNum(int min, int max)
{
    static std::default_random_engine engine;
    static std::uniform_int_distribution<> distribution(min, max);
    return distribution(engine);
}
