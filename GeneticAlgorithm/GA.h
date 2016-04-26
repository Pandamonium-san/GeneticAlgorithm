#pragma once
#include <map>
#include "Population.h"
#include <random>

class City;
class Tour;

class GA
{
public:
	GA();

	void CreateMap();
	std::map<int, City*>& GetCities();
	City* GetCity(int key);
	Population* CreatePopulation(int popSize);
	Population EvolvePopulation(Population& pop);
	Tour CalculateGeneticTour(int generations, int popSize);
	int GetNrOfCities(){ return nrOfCities; }
	void WriteToFile();
	void WriteFitness();
	void PrintPopulation();
	void PrintFitness();

	std::mt19937 rng;

private:
	Tour Crossover(Tour& parent1, Tour& parent2);
	void Mutate(Tour& tour);
	Tour TournamentSelection(Population& pop);
	Tour RouletteSelection(Population& pop);

	int nrOfCities;
	std::map<int, City*> cities;
	Population population;
	int generation = 1;

	double mutationRate = 0.015;
	int tournamentSize = 5;
	bool elitism = true;
	std::vector<double> fitnessData;
};
