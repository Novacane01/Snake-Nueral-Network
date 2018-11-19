#pragma once
#include "Snake.h"
#include "NeuralNetwork.h"

class DNA
{
public:
	DNA(int,int,int);
	void Update(float dt,Floor *);
	void Draw(sf::RenderWindow &);
	void mutate();
	DNA *crossOver(DNA *);
	LinkedSnake *snake = nullptr;
	NeuralNetwork nn;
	int il, hl, ol;
	float fitness = 5;
	int length = 1;
	~DNA();
};

