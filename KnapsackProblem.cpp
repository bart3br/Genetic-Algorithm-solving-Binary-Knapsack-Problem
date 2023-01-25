#include "KnapsackProblem.h"

KnapsackProblem::KnapsackProblem()
{
	numberOfItems = 0;
	knapsackCapacity = 0.0;
}
KnapsackProblem::KnapsackProblem(std::string filename)
{
	try
	{
		readFromFile(filename);
	}
	catch (const std::exception& e)
	{
		throw;
	}

	if (numberOfItems < 1)
		throw std::invalid_argument("Incorrect numberOfItems");
	if (knapsackCapacity <= 0.0)
		throw std::invalid_argument("Incorrect knapsackCapacity");
	if (values.size() != numberOfItems || weights.size() != numberOfItems)
		throw std::invalid_argument("Incorrect number of item's data");
	for (int i = 0; i < numberOfItems; i++)
	{
		if (values[i] <= 0.0 || weights[i] <= 0.0)
			throw std::invalid_argument("One of the items has incorrect value or weight");
	}
}
KnapsackProblem::KnapsackProblem(const KnapsackProblem& other)
{
	numberOfItems = other.numberOfItems;
	knapsackCapacity = other.knapsackCapacity;
	values = other.values;
	weights = other.weights;
}
KnapsackProblem::KnapsackProblem(KnapsackProblem&& other) noexcept
{
	numberOfItems = other.numberOfItems;
	knapsackCapacity = other.knapsackCapacity;
	values = other.values;
	weights = other.weights;

	other.numberOfItems = 0;
	other.knapsackCapacity = 0.0;
	other.values.clear();
	other.weights.clear();
}
KnapsackProblem::~KnapsackProblem() 
{
	values.clear();
	weights.clear();
}

//operator=
KnapsackProblem& KnapsackProblem::operator= (const KnapsackProblem& other)
{
	if (this == &other)
		return (*this);

	values.clear();
	weights.clear();
	
	numberOfItems = other.numberOfItems;
	knapsackCapacity = other.knapsackCapacity;
	values = other.values;
	weights = other.weights;

	return (*this);
}
KnapsackProblem& KnapsackProblem::operator= (KnapsackProblem&& other) noexcept
{
	if (this == &other)
		return (*this);

	values.clear();
	weights.clear();

	numberOfItems = other.numberOfItems;
	knapsackCapacity = other.knapsackCapacity;
	values = other.values;
	weights = other.weights;

	other.numberOfItems = 0;
	other.knapsackCapacity = 0.0;
	other.values.clear();
	other.weights.clear();

	return (*this);
}

void KnapsackProblem::readFromFile(std::string filename)
{
	std::ifstream is (filename);
	if (!is.is_open())
		throw std::ios_base::failure("Couldn't open the file: '" + filename + "'");
	
	is >> numberOfItems;
	is >> knapsackCapacity;

	double val;
	double wei;
	while (is >> val >> wei)
	{
		values.push_back(val);
		weights.push_back(wei);
	}

	is.close();
}

double KnapsackProblem::evaluate(const std::vector<bool>& genotype) 
{
	double fitness = 0.0;
	double weight = 0.0;
	for (int i = 0; i < genotype.size(); i++) {
		if (genotype[i] == true) {
			fitness += values[i];
			weight += weights[i];
		}
	}

	if (weight > knapsackCapacity)
		return 0.0;

	return fitness;
}

int KnapsackProblem::getNumberOfItems() { return numberOfItems; }
double KnapsackProblem::getKnapsackCapacity() { return knapsackCapacity; }
std::vector<double>& KnapsackProblem::getValues() { return values; }
std::vector<double>& KnapsackProblem::getWeights() { return weights; }

