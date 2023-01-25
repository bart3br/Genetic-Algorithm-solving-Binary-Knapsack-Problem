#include "RandomGenerator.h"

RandomGenerator::RandomGenerator() :
	gen((std::random_device())())
{
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<> dist;
}

int RandomGenerator::randomInt(int min, int max) 
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

double RandomGenerator::randomDouble(double min, double max)
{
	std::uniform_real_distribution<double> dist(min, max);
	return dist(gen);
}

