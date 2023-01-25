#pragma once
#include <vector>
#include <utility>
#include "KnapsackProblem.h"
#include "Individual.h"
#include "RandomGenerator.h"
#include "MySmartPointer.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm() = delete;
	GeneticAlgorithm(int ipopSize, double dcrossProb, double dmutProb, int iiterCount, KnapsackProblem& oproblem);
	~GeneticAlgorithm();

	void run();
	
private:
	int popSize;
	double crossProb;
	double mutProb;
	int iterCount;
	Individual bestIndividual;
	KnapsackProblem problem;
	std::vector<MySmartPointer<Individual>> population;
	RandomGenerator generator;

	void generateFirstPopulation();
	void countPopulationFitness();
	void crossPopulation();
	std::pair<int, int> chooseParents();
	void mutatePopulation();

};

