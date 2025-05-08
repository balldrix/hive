#pragma once

#include <random>

class Randomiser
{
public:
	~Randomiser();

	static Randomiser* Instance();
	
	double GetRandNumUniform(double min, double max);
	float GetRandNumUniform(float min, float max);
	int GetRandNumUniform(int min, int max);

	float GetRandNumNormal(float min, float max);

private:
	std::mt19937 m_generator;
	Randomiser();
};