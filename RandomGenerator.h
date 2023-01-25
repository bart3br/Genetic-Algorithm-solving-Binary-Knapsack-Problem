#pragma once
#include <random>

class RandomGenerator
{
public:
	RandomGenerator();
	int randomInt(int min, int max);
	double randomDouble(double min, double max);
private:
	//std::random_device rd;
	std::mt19937 gen;
	//std::uniform_int_distribution<> dist;
};

