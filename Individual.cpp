#include "Individual.h"

Individual::Individual()
{
	fitness = 0.0;
}
Individual::Individual(std::vector <bool>& vgenotype) 
{
	genotype = vgenotype;
	fitness = 0.0;
}
Individual::Individual(const Individual& other) 
{
	for (int i = 0; i < other.genotype.size(); i++) {
		genotype.push_back(other.genotype[i]);
	}
	fitness = other.fitness;
}
Individual::Individual(Individual&& other) noexcept
{
	genotype = std::move(other.genotype);
	fitness = other.fitness;

	other.genotype.clear();
	other.fitness = 0.0;
}
Individual::~Individual() 
{
	genotype.clear();
}


Individual& Individual::operator=(const Individual& other) 
{
	if (this == &other)
		return (*this);
	
	genotype.clear();

	for (int i = 0; i < other.genotype.size(); i++) {
		genotype.push_back(other.genotype[i]);
	}
	fitness = other.fitness;

	return (*this);
}
Individual& Individual::operator=(Individual&& other) noexcept
{
	if (this == &other)
		return (*this);

	genotype.clear();
	genotype = std::move(other.genotype);
	fitness = other.fitness;

	other.genotype.clear();
	other.fitness = 0.0;

	return (*this);
}
bool Individual::operator==(const Individual& other) const
{
	if (genotype.size() != other.genotype.size() || fitness != other.fitness)
		return false;

	for (int i = 0; i < genotype.size(); i++) 
	{
		if (genotype[i] != other.genotype[i])
			return false;
	}

	return true;
}


std::pair<Individual*, Individual*> Individual::cross(const Individual& other, double crossProb, RandomGenerator& generator) const
{
	//we return a local variable not through reference, RVO makes sure no copies are made

	int size = genotype.size();
	double crossing = generator.randomDouble(0.0, 1.0);

	if (crossing < crossProb) 
	{
		int cutGenotype = generator.randomInt(1, size - 1);
		std::vector<bool> gen1;
		std::vector<bool> gen2;

		for (int i = 0; i < cutGenotype; i++) 
		{
			gen1.push_back(genotype[i]);
			gen2.push_back(other.genotype[i]);
		}
		for (int i = cutGenotype; i < size; i++) 
		{
			gen1.push_back(other.genotype[i]);
			gen2.push_back(genotype[i]);
		}

		//crossing happened, so using parameter constructor, returning pointers to new children after crossing
		return std::make_pair(new Individual(gen1), new Individual(gen2));
	}
	else
	{
		//crossing didn't happen, so returning nullptrs, then in AG making copies of SmartPointers to parents
		return std::make_pair(nullptr, nullptr);
	}
}

void Individual::mutate(double mutProb, RandomGenerator& generator)
{
	for (int i = 0; i < genotype.size(); i++)
	{
		double mutation = generator.randomDouble(0.0, 1.0);
		if (mutation < mutProb)
			genotype[i] = !genotype[i];
	}
}

double Individual::evaluate(KnapsackProblem& problem)
{
	double fit = problem.evaluate(genotype);
	setFitness(fit);
	return fit;
}

double Individual::getFitness() { return fitness; }
void Individual::setFitness(double newFit) { fitness = newFit; }

void Individual::print()
{
	std::cout << "Individual: genotype = [ ";
	for (bool b : genotype)
	{
		if (b == true)
			std::cout << 1 << " ";
		else std::cout << 0 << " ";
	}
	std::cout << "]; fitness = " << fitness << std::endl;
}
