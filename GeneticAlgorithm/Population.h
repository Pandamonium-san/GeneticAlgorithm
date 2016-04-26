#pragma once
#include <vector>
#include "Tour.h"

class GA;

class Population
{
public:
	Population(){};
	Population(int populationSize, GA* ga);
	Population(GA* ga){ this->ga = ga; };
	~Population(){ tours.clear(); }

	void AddTour(Tour tour);
	void SetTour(int index, Tour tour);
	Tour GetTour(int index);
	Tour GetFittest();
	int GetPopSize();
	void SortAccordingToFitness();

	double Best();
	double Worst();
	double Median();
	double Average();
	double StdDev();

private:
	std::vector<Tour> tours = std::vector<Tour>(0);
	GA* ga;
};