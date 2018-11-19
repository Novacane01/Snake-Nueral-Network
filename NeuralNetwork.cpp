#include "stdafx.h"
#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(int il, int hl, int ol):input_layer(il,1),hidden_layer(hl,1),output_layer(ol,1),weights_ih(hl,il),weights_ho(ol,hl){
	weights_ih.randomize();
	weights_ho.randomize();
	bias_ih = (float)rand() / RAND_MAX;
	bias_ho = (float)rand() / RAND_MAX;
}

Matrix NeuralNetwork::fromArray(std::vector<float> input) {
	Matrix newMatrix(input.size(), 1);
	for (unsigned i = 0;i < input.size();i++) {
		newMatrix.matrix[i][0] = input[i];
	}
	return newMatrix;
}

std::vector<float> NeuralNetwork::toArray(Matrix *input) {
	std::vector<float> newVector;
	for (unsigned i = 0;i < input->rows;i++) {
		for (unsigned j = 0;j < input->columns;j++) {
			newVector.push_back(input->matrix[i][j]);
		}
	}
	return newVector;
}

std::vector<float> NeuralNetwork::getOutput(){
	return toArray(&output_layer);
}
void NeuralNetwork::feedforward(std::vector<float> input_array) {
	input_layer = fromArray(input_array);
	hidden_layer = weights_ih.multiply(&input_layer);
	hidden_layer = hidden_layer.add(bias_ih);
	output_layer = weights_ho.multiply(&hidden_layer);
	output_layer = output_layer.add(bias_ho);
	output_layer = output_layer.sigmoid();
}

NeuralNetwork::~NeuralNetwork()
{
}
