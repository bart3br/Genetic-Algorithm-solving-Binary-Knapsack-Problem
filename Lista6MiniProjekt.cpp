#include <iostream>
#include <string>
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"

void runMultipleFiles(int numberOfFiles, int popSize, double crossProb, double mutProb, int iterCount)
{
    std::string filename;
    for (int i = 1; i <= numberOfFiles; i++)
    {
        filename = "kp" + std::to_string(i) + ".txt";
        std::cout << "File: " << filename << "\n\n";

        try
        {
            KnapsackProblem problem(filename);
            GeneticAlgorithm ag(popSize, crossProb, mutProb, iterCount, problem);
            ag.run();
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception: " << e.what() << "; " << typeid(e).name() << std::endl;
        }
        catch (...)
        {
            std::cout << "Unknown exception\n";
        }
        std::cout << "\n----------------------------------------------------------------------------------------------------------\n";
    }
}
void run(std::string filename, int numberOfFiles, int popSize, double crossProb, double mutProb, int iterCount)
{
    try
    {
        KnapsackProblem problem(filename);
        GeneticAlgorithm ag(popSize, crossProb, mutProb, iterCount, problem);
        ag.run();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "; " << typeid(e).name() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception\n";
    }
}

int main()
{
    std::string filename = "kp1.txt";
    int numberOfFiles = 5;
    int popSize = 10;
    double crossProb = 0.6;
    double mutProb = 0.1;
    int iterCount = 20;

    run(filename, numberOfFiles, popSize, crossProb, mutProb, iterCount);
    //runMultipleFiles(numberOfFiles, popSize, crossProb, mutProb, iterCount);

    return 0;
}