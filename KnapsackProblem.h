#pragma once
#include <vector>
#include <fstream>

class KnapsackProblem
{
public:
	KnapsackProblem();
	KnapsackProblem(std::string filename);
	KnapsackProblem(const KnapsackProblem& other);
	KnapsackProblem(KnapsackProblem&& other) noexcept;
	~KnapsackProblem();

	KnapsackProblem& operator= (const KnapsackProblem& other);
	KnapsackProblem& operator= (KnapsackProblem&& other) noexcept;

	void readFromFile(std::string filename);
	double evaluate(const std::vector <bool>& genotype);

	int getNumberOfItems();
	double getKnapsackCapacity();
	std::vector<double>& getValues();
	std::vector<double>& getWeights();
	
private:
	int numberOfItems;
	double knapsackCapacity;
	std::vector <double> values;
	std::vector <double> weights;
};

