#include "GA.h"
#include "GameObject.h"
#include "City.h"
#include <random>
#include <iostream>
#include <fstream>
#include "Utility.h"
#include <time.h>

GA::GA()
{
	rng = std::mt19937(time(NULL));
}

void GA::CreateMap()
{
	std::fstream stream;
	stream.open("logs/cities.txt");

	std::list<GameObject*> out;
	game.FindAllGameObjOfType(GameObject::TYPE_CITY, out);

	int i = 0;
	std::list<GameObject*>::iterator itr;
	for (itr = out.begin(); itr != out.end(); ++itr)
	{
		City* c = dynamic_cast<City*>(*itr);
		cities.insert(std::pair<int, City*>(i++, c));
		stream << c->body.getPosition().x << "," << c->body.getPosition().y << std::endl;
	}
	stream.close();
	nrOfCities = cities.size();
}

Population* GA::CreatePopulation(int popSize)
{
	population = Population(popSize, this);
	return &population;
}

Tour GA::CalculateGeneticTour(int generations, int popSize)
{
	CreateMap();

	population = Population(popSize, this);
	population.SortAccordingToFitness();

	WriteToFile();
	fitnessData.push_back(population.GetFittest().GetDistance());
	//PrintPopulation();
	std::cout << generation << ". ";
	PrintFitness();

	for (size_t i = 1; i < generations; i++)
	{
		population = EvolvePopulation(population);
		fitnessData.push_back(population.GetFittest().GetDistance());
		if (generation == 10 || generation == 100 || generation == 1000 || generation == 10000)
		{
			WriteToFile();
		}
		std::cout << generation << ". ";
		PrintFitness();
		//PrintPopulation();
	}
	population.SortAccordingToFitness();
	WriteFitness();
	return population.GetFittest();
}

Population GA::EvolvePopulation(Population& pop)
{
	Population newPopulation = Population(this);

	int elitismOffset = 0;
	if (elitism)
	{
		newPopulation.AddTour(pop.GetFittest());
		elitismOffset = 1;
	}

	for (size_t i = elitismOffset; i < pop.GetPopSize(); i++)
	{
		Tour parent1 = TournamentSelection(pop);
		Tour parent2 = TournamentSelection(pop);
		Tour child = Tour(parent1.GetSize(), this);
		child = Crossover(parent1, parent2);

		//Guranteed mutation if child is copy of parent, important in order to maintain diversity.
		if (child == parent1 || child == parent2)
			Mutate(child);
		
		newPopulation.AddTour(child);
	}

	for (size_t i = 0; i < newPopulation.GetPopSize(); i++)
	{
		double r = 1 - (double)rand() / RAND_MAX;
		if (r < mutationRate)
			Mutate(newPopulation.GetTour(i));
	}
	generation += 1;
	return newPopulation;
}

Tour GA::Crossover(Tour& parent1, Tour& parent2)
{
	int tourSize = parent1.GetSize();
	Tour child = Tour(tourSize, this);

	//randomize subtour from parent1
	int startPos = 0;
	int endPos = 0;
	//while (startPos == endPos)
	{
		std::uniform_int_distribution<> x(0, tourSize - 1);
		startPos = x(rng);
		endPos = x(rng);
	}

	//insert subtour
	if (startPos < endPos)
	{
		for (size_t i = 0; i < tourSize; i++)
		{
			if (startPos < i && i < endPos)
				child.SetValue(i, parent1.GetValue(i));
		}
	}
	else if (endPos < startPos)
	{
		for (size_t i = 0; i < tourSize; i++)
		{
			if (!(startPos < i && i < endPos))
				child.SetValue(i, parent1.GetValue(i));
		}
	}

	//fill empty positions from parent2
	for (size_t i = 0; i < tourSize; i++)
	{
		int parentValue = parent2.GetValue(i);
		if (!child.ContainsValue(parent2.GetValue(i)))
		{
			for (size_t j = 0; j < tourSize; j++)
			{
				if (child.GetValue(j) == -1)
				{
					child.SetValue(j, parent2.GetValue(i));
					break;
				}
			}
		}
	}

	//parent1.PrintSequence();
	//parent2.PrintSequence();
	//child.PrintSequence();
	//std::cout << std::endl;

	return child;
}

void GA::Mutate(Tour& tour)
{
	int tourPos1 = rand() % tour.GetSize();
	int tourPos2 = rand() % tour.GetSize();

	int city1 = tour.GetValue(tourPos1);
	int city2 = tour.GetValue(tourPos2);

	tour.SetValue(tourPos2, city1);
	tour.SetValue(tourPos1, city2);
}

Tour GA::TournamentSelection(Population& pop)
{
	Population tournament = Population(this);
	std::uniform_int_distribution<> x(0, pop.GetPopSize()-1);
	for (size_t i = 0; i < tournamentSize; i++)
	{
		int random = x(rng);
		tournament.AddTour(pop.GetTour(random));
	}
	Tour fittest = tournament.GetFittest();
	//Tour fittest = RouletteSelection(tournament);
	return fittest;
}

Tour GA::RouletteSelection(Population& pop)
{
	pop.SortAccordingToFitness();
	double sumOfFitness = 0;
	for (size_t i = 0; i < pop.GetPopSize(); i++)
	{
		sumOfFitness += pop.GetTour(i).GetFitness();
	}
	double a = rand();
	double b = RAND_MAX;
	double r = a / b;
	double value = r * sumOfFitness;
	for (size_t i = 0; i < pop.GetPopSize(); i++)
	{
		value -= pop.GetTour(i).GetFitness();
		if (value <= 0)
			return pop.GetTour(i);
	}
	return pop.GetTour(0);
}

City* GA::GetCity(int key)
{
	return cities[key];
}

std::map<int, City*>& GA::GetCities()
{
	return cities;
}

void GA::PrintPopulation()
{
	std::cout << "Generation " << generation << std::endl;
	std::cout << "Fittest: " << population.GetFittest().GetDistance();
	for (size_t i = 0; i < population.GetPopSize(); i++)
	{
		std::cout << population.GetTour(i).GetDistance() << std::endl;
	}
}

void GA::PrintFitness()
{
	std::cout << "Distance: " << population.GetFittest().GetDistance() << std::endl;
}

void GA::WriteToFile()
{
	std::ofstream stream;
	stream.open("logs/generation" + Utility::ToString(generation) + ".txt");
	stream << "Generation " << generation << std::endl;
	stream << "Population size: " << population.GetPopSize() << std::endl;
	stream << "Best: " << population.Best() << std::endl;
	stream << "Worst: " << population.Worst() << std::endl;
	stream << "Median: " << population.Median() << std::endl;
	stream << "Average: " << population.Average() << std::endl;
	stream << "Deviation: " << population.StdDev() << std::endl;
	stream << std::endl;
	stream.close();
}

void GA::WriteFitness()
{
	std::ofstream stream;
	stream.open("logs/fitnessData.txt");
	std::vector<double>::iterator itr;
	for (itr = fitnessData.begin(); itr != fitnessData.end(); ++itr)
	{
		stream << *itr;
		stream << std::endl;
	}
	stream.close();
}

