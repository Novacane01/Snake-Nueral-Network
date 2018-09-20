#pragma once
#include "Matrix.h"
class NueralNetwork
{
public:
	NueralNetwork(int,int,int);
	void feedforward(std::vector<double>);
	Matrix fromArray(std::vector<double>);
	~NueralNetwork();

private:
	Matrix input_layer, hidden_layer, output_layer;
	Matrix weights_ih, weights_ho;
	float bias_ih, bias_ho;
};

