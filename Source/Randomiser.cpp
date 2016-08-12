#include "Randomiser.h"
#include "Time.h"
#include "stdlib.h"


Randomiser::Randomiser()
{
	srand((int)time(NULL));
}

Randomiser::Randomiser(int seed)
{
	srand(seed);
}

Randomiser::~Randomiser()
{

}

