#pragma once
#include "Matrix.h"

extern float mutationRate;

class NeuralNetwork
{
public:
	NeuralNetwork(int,int,int);
	void feedforward(std::vector<float>);
	Matrix fromArray(std::vector<float>);
	std::vector<float> toArray(Matrix *);
	std::vector<float> getOutput();
	~NeuralNetwork();

	Matrix input_layer, hidden_layer, output_layer;
	Matrix weights_ih, weights_ho;
	float bias_ih, bias_ho;
};

