#include "stdafx.h"
#include "Population.h"


Population::Population(int il, int hl, int ol, const int size):size(size){
	for (unsigned i = 0;i < size;i++) {
		population.push_back(new DNA(il,hl,ol));
	}
	this->il = il;
	this->hl = hl;
	this->ol = ol;
}

void Population::calcFitness() {
	float totalFitness = 0.f;
	for (DNA * d : population) {
		totalFitness += d->fitness;
	}
	for (DNA *d : population) {
		d->fitness /= totalFitness;
	}
}

DNA *Population::selectParent(std::vector<DNA *> genepool) {
	
	unsigned index = 0;
	for (float r = (float)rand() / RAND_MAX, i = 0;r > 0&&i<genepool.size(); i++) {
		r -= genepool[index]->fitness;
		index = i;
	}
	return genepool[index];
}

DNA *Population::selectElite(std::vector<DNA *> genepool) {
	DNA *elitist = new DNA(il, hl, ol);
	float max = 0.f;
	unsigned elite_index = 0;
	for (unsigned i = 0;i < genepool.size();i++) {
		if (genepool[i]->fitness > max) {
			max = genepool[i]->fitness;
			elite_index = i;
		}
	}
	for (unsigned i = 0;i < elitist->nn.weights_ih.matrix.size();i++) {
		for (unsigned j = 0;j < elitist->nn.weights_ih.matrix[i].size();j++) {
			elitist->nn.weights_ih.matrix[i][j] = genepool[elite_index]->nn.weights_ih.matrix[i][j];
		}
	}
	for (unsigned i = 0;i < elitist->nn.weights_ho.matrix.size();i++) {
		for (unsigned j = 0;j < elitist->nn.weights_ho.matrix[i].size();j++) {
			elitist->nn.weights_ho.matrix[i][j] = genepool[elite_index]->nn.weights_ho.matrix[i][j];
		}
	}
	elitist->nn.bias_ih = genepool[elite_index]->nn.bias_ih;
	elitist->nn.bias_ho = genepool[elite_index]->nn.bias_ho;
	elitist->snake->body.front().body.setFillColor(sf::Color::Red);
	return elitist;
}


Population::~Population()
{
	for (DNA *s : population) {
		delete s;
	}
}
