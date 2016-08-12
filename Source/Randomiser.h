#ifndef _RANDOMISER_H_
#define _RANDOMISER_H_

class Randomiser
{
public:
	Randomiser();
	Randomiser(int seed);
	~Randomiser();

	template<typename T>
	static T GetRandNum(T min, T max);

private:

};

template<typename T>
T
Randomiser::GetRandNum(T min, T max)
{
	T range = max - min + 1;
	return (rand() % range) + min;
}

#endif _RANDOMISER_H_

