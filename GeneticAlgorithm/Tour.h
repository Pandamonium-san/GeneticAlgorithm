#pragma once
#include <vector>
#include <string>

class GA;
class Tour
{
public:
	Tour(int size, GA* ga);
	Tour(){};
	~Tour();

	void GenerateSequence();
	int GetValue(int position);
	void SetValue(int position, int value);
	bool ContainsValue(int value);
	double GetFitness();
	double GetDistance();
	int GetSize(){ return size; }
	void PrintSequence();
	bool operator==(const Tour& other);
	bool operator<(Tour& other);

private:
	GA* ga;
	double fitness;
	double distance;
	std::vector<int> sequence;
	int size;
};