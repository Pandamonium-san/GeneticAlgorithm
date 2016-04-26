#include "Tour.h"
#include <algorithm>
#include "GA.h"
#include "Utility.h"
#include "City.h"
#include <iostream>

Tour::Tour(int size, GA* ga)
{
	this->size = size;
	this->ga = ga;
	sequence.resize(size, -1);
}

Tour::~Tour()
{
	sequence.clear();
}

void Tour::GenerateSequence()
{
	for (size_t i = 0; i < size; i++)
	{
		sequence[i] = i;
	}
	std::random_shuffle(sequence.begin(), sequence.end());
}

void Tour::SetValue(int position, int value)
{
	sequence[position] = value;
	fitness = 0;
	distance = 0;
}

int Tour::GetValue(int position)
{
	return sequence[position];
}

bool Tour::ContainsValue(int value)
{
	std::vector<int>::iterator itr;
	for (itr = sequence.begin(); itr != sequence.end(); itr++)
	{
		if (*itr == value)
			return true;
	}
	return false;
}

double Tour::GetFitness()
{
	if (fitness > 0)
		return fitness;

	fitness = 1 / GetDistance() * 1000;
	return fitness;
}

double Tour::GetDistance()
{
	if (distance > 0)
		return distance;

	double distance = 0;
	for (size_t i = 0; i < size; i++)
	{
		City* a = ga->GetCity(sequence[i]);
		City* b;
		if (i + 1 < size)
			b = ga->GetCity(sequence[i + 1]);
		else
			b = ga->GetCity(sequence[0]);
		distance += Utility::DistanceBetweenVectors(a->body.getPosition(), b->body.getPosition());
	}
	this->distance = distance;
	return distance;
}

void Tour::PrintSequence()
{
	std::cout << "[";
	std::vector<int>::iterator itr;
	for (itr = sequence.begin(); itr != sequence.end(); itr++)
	{
		std::cout << *itr << ", ";
	}
	std::cout << "]" << std::endl;
}

bool Tour::operator==(const Tour& other)
{
	return other.sequence == this->sequence;
}

bool Tour::operator<(Tour& other)
{
	return GetFitness() < other.GetFitness();
}