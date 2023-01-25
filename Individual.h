#pragma once
#include <vector>
#include <iostream>
#include "KnapsackProblem.h"
#include "RandomGenerator.h"

class Individual
{
public:
	Individual();
	Individual(std::vector <bool>& vgenotype);
	Individual(const Individual& other);
	Individual(Individual&& other) noexcept;
	~Individual();
	
	Individual& operator= (const Individual& other);
	Individual& operator= (Individual&& other) noexcept;
	bool operator==(const Individual& other) const;

	std::pair<Individual*, Individual*> cross(const Individual& other, double crossProb, RandomGenerator& generator) const;
	void mutate(double mutProb, RandomGenerator& generator);
	double evaluate(KnapsackProblem& problem); //countFitness

	double getFitness();
	void setFitness(double newFit);
	void print();

private:
	std::vector <bool> genotype;
	double fitness;
};

