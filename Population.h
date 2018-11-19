#pragma once
#include "Matrix.h"
#include "DNA.h"

class Population
{
public:
	Population(int,int,int,const int);
	DNA *selectElite(std::vector<DNA*>);
	DNA *selectParent(std::vector<DNA *> );
	void calcFitness();
	std::vector<DNA *> population;
	unsigned generation = 0;
	~Population();
private:
	int il, hl, ol;
	const int size;
	float bias = 0.f;
};

