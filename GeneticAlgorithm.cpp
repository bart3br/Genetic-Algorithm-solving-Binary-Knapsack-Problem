#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int ipopSize, double dcrossProb, double dmutProb, int iiterCount, KnapsackProblem& oproblem)
{
	popSize = ipopSize;
	crossProb = dcrossProb;
	mutProb = dmutProb;
	iterCount = iiterCount;
	problem = oproblem;

	if (popSize <= 1)
		throw std::invalid_argument("Incorrect value of popSize");
	if (crossProb < 0.0 || crossProb > 1.0)
		throw std::invalid_argument("Incorrect value of crossProb");
	if (mutProb < 0.0 || mutProb > 1.0)
		throw std::invalid_argument("Incorrect value of mutProb");
	if (iterCount < 1)
		throw std::invalid_argument("Incorrect value of iterCount");
	
}
GeneticAlgorithm::~GeneticAlgorithm()
{
	population.clear();
}

void GeneticAlgorithm::run()
{
	generateFirstPopulation();

	for (int i = 0; i < iterCount; i++)
	{
		countPopulationFitness();

		//std::printf("%s%-4d%-5s%s", "iteration nr: ", i, "", "current bestIndividual: ");
		//bestIndividual.print();

		crossPopulation();
		mutatePopulation();
	}
	std::cout << "bestIndividual: ";
	bestIndividual.print();
}

void GeneticAlgorithm::generateFirstPopulation()
{
	int genLength = problem.getNumberOfItems();

	for (int i = 0; i < popSize; i++)
	{
		std::vector<bool> genotype;
		for (int j = 0; j < genLength; j++)
		{
			int gen = generator.randomInt(0, 1);

			if (gen == 0)
				genotype.push_back(false);
			else 
				genotype.push_back(true);
		}
		population.push_back(MySmartPointer<Individual>(new Individual(genotype)));
	}
}

void GeneticAlgorithm::countPopulationFitness()
{
	bestIndividual.evaluate(problem);
	double maxFit = 0.0;
	int maxIndx = 0;

	for (int i=0; i<population.size(); i++)
	{
		double fit = population[i]->evaluate(problem);

		if (fit > maxFit)
		{
			maxFit = fit;
			maxIndx = i;
		}
	}
	
	if (maxFit > bestIndividual.getFitness())
		bestIndividual = (*population[maxIndx]);
}

void GeneticAlgorithm::crossPopulation()
{
	int counterOfNewPop = 0;
	std::vector <MySmartPointer<Individual>> newPopulation;

	while (counterOfNewPop < popSize)
	{
		std::pair<int, int> parents = chooseParents();
		std::pair<Individual*, Individual*> children = population[parents.first]->cross(*population[parents.second], crossProb, generator);
		//checking if crossing happened. if not, then adding copies of MySmartPointer (parents) to newPopulation
		if (children.first == nullptr && children.second == nullptr)
		{
			newPopulation.push_back(MySmartPointer<Individual>(population[parents.first]));
			counterOfNewPop++;

			if (counterOfNewPop < popSize)
			{
				newPopulation.push_back(MySmartPointer<Individual>(population[parents.second]));
				counterOfNewPop++;
			}
		}
		else //crossing happened, children is a pair of new Individuals, so just adding them to newPopulation
		{
			newPopulation.push_back(MySmartPointer<Individual>(children.first));
			counterOfNewPop++;

			if (counterOfNewPop < popSize)
			{
				newPopulation.push_back(MySmartPointer<Individual>(children.second));
				counterOfNewPop++;
			}
		}
	}
	population.clear();
	population = newPopulation;
}

std::pair<int, int> GeneticAlgorithm::chooseParents()
{
	int candidate1 = generator.randomInt(0, popSize - 1);
	int candidate2 = generator.randomInt(0, popSize - 1);
	//to make sure that candidate1 != candidate2
	while (candidate2 == candidate1)
		candidate2 = generator.randomInt(0, popSize - 1);

	int parent1;
	if (population[candidate1]->getFitness() >= population[candidate2]->getFitness())
		parent1 = candidate1;
	else
		parent1 = candidate2;

	int parent2;
	candidate1 = generator.randomInt(0, popSize - 1);
	candidate2 = generator.randomInt(0, popSize - 1);
	//to make sure that candidate1 != candidate2
	while (candidate2 == candidate1)
		candidate2 = generator.randomInt(0, popSize - 1);

	//if either of the second pair of candidates is already chosen as parent1, then parent2 will be the other candidate
	if (candidate1 == parent1)
		parent2 = candidate2;
	else if (candidate2 == parent1)
		parent2 = candidate1;
	else
	{
		if (population[candidate1]->getFitness() >= population[candidate2]->getFitness())
			parent2 = candidate1;
		else
			parent2 = candidate2;
	}
	return std::make_pair(parent1, parent2);
}

void GeneticAlgorithm::mutatePopulation()
{
	for (int i = 0; i < population.size(); i++)
	{
		population[i]->mutate(mutProb, generator);
	}
}

