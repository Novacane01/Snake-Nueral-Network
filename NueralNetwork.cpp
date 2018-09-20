#include "stdafx.h"
#include "NueralNetwork.h"


NueralNetwork::NueralNetwork(int il, int hl, int ol):input_layer(il,1),hidden_layer(hl,1),output_layer(ol,1),weights_ih(hl,il),weights_ho(ol,hl){
	weights_ih.randomize();
	weights_ho.randomize();
	bias_ih = rand() / RAND_MAX;
	bias_ho = rand() / RAND_MAX;
}

Matrix NueralNetwork::fromArray(std::vector<double> input) {
	Matrix newMatrix(input.size(), 1);
	for (unsigned i = 0;i < input.size();i++) {
		newMatrix.matrix[i][0] = input[i];
	}
	return newMatrix;
}

void NueralNetwork::feedforward(std::vector<double> input_array) {
	input_layer = fromArray(input_array);
	hidden_layer = weights_ih.multiply(&input_layer);
	hidden_layer = hidden_layer.add(bias_ih);
	output_layer = weights_ho.multiply(&hidden_layer);
	output_layer = output_layer.add(bias_ho);
	output_layer = output_layer.sigmoid();
}

NueralNetwork::~NueralNetwork()
{
}
