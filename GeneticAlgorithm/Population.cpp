#include "Population.h"
#include "GA.h"
#include <algorithm>
#include <cmath>

Population::Population(int populationSize, GA* ga)
{
	this->ga = ga;
	for (size_t i = 0; i < populationSize; i++)
	{
		Tour* tour = new Tour(ga->GetNrOfCities(), ga);
		tour->GenerateSequence();
		tours.push_back(*tour);
	}
}

void Population::SortAccordingToFitness()
{
	std::sort(tours.begin(), tours.end());
	std::reverse(tours.begin(), tours.end());
}

void Population::AddTour(Tour tour)
{
	tours.push_back(tour);
}

void Population::SetTour(int index, Tour tour)
{
	tours[index] = tour;
}

Tour Population::GetTour(int index)
{
	return tours[index];
}

Tour Population::GetFittest()
{
	Tour fittest = tours[0];
	for (size_t i = 0; i < tours.size(); i++)
	{
		if (fittest.GetFitness() < tours[i].GetFitness())
			fittest = tours[i];
	}
	return fittest;
}

int Population::GetPopSize()
{
	return tours.size();
}

double Population::Best(){ return GetFittest().GetDistance(); }
double Population::Worst(){ return GetTour(GetPopSize() - 1).GetDistance(); }
double Population::Median(){ return GetTour(GetPopSize() / 2).GetDistance(); }
double Population::Average()
{
	double total = 0;
	for (size_t i = 0; i < tours.size(); i++)
	{
		total += tours[i].GetDistance();
	}
	return total / (double)tours.size();
}
double Population::StdDev()
{
	double average = Average();
	double variance = 0;
	for (size_t i = 0; i < tours.size(); i++)
	{
		variance += pow((tours[i].GetDistance() - average), 2);
	}
	variance = variance / tours.size();
	return sqrt(variance);
}