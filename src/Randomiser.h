#pragma once

#include <random>

class Randomiser
{
public:

	static double GetRandNumUniform(double min, double max);
	static float GetRandNumUniform(float min, float max);
	static int GetRandNumUniform(int min, int max);
	static float GetRandNumNormal(float min, float max);

private:
	static std::mt19937 s_generator;
};