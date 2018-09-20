#pragma once
#include "Matrix.h"
#include "DNA.h"

class Population
{
public:
	Population(int);
	void feedForward(Matrix *);
	DNA selectElite();
	DNA selectParent();
	~Population();
private:
	const int size;
	std::vector<DNA> population;
	float bias;
	float mutationRate;
};

