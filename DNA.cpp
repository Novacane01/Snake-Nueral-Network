#include "stdafx.h"
#include "DNA.h"

float mutationRate = .05f;

DNA::DNA(int il, int hl, int ol) :nn(il,hl,ol) {
	snake = new LinkedSnake();
	this->il = il;
	this->hl = hl;
	this->ol = ol;
}

DNA * DNA::crossOver(DNA *parentB) {
	DNA *child = new DNA(il,hl,ol);
	float r;
	for (unsigned i = 0;i < nn.weights_ih.matrix.size();i++) {
		for (unsigned j = 0;j < nn.weights_ih.matrix[i].size();j++) {
			r = (float)rand() / RAND_MAX;
			if (r > 5) {
				child->nn.weights_ih.matrix[i][j] = nn.weights_ih.matrix[i][j];
			}
			else {
				child->nn.weights_ih.matrix[i][j] = parentB->nn.weights_ih.matrix[i][j];
			}
		}
	}
	if (r > .5f) {
		child->nn.bias_ih = nn.bias_ih;
	}
	else {
		child->nn.bias_ih = parentB->nn.bias_ih;
	}
	for (unsigned i = 0;i < nn.weights_ho.matrix.size();i++) {
		for (unsigned j = 0;j < nn.weights_ho.matrix[i].size();j++) {
			r = (float)rand() / RAND_MAX;
			if (r > 5) {
				child->nn.weights_ho.matrix[i][j] = nn.weights_ho.matrix[i][j];
			}
			else {
				child->nn.weights_ho.matrix[i][j] = parentB->nn.weights_ho.matrix[i][j];
			}
		}
	}
	if (r > .5f) {
		child->nn.bias_ho = nn.bias_ho;
	}
	else {
		child->nn.bias_ho = parentB->nn.bias_ho;
	}
	return child;
}

void DNA::mutate() {
	float r;
	for (unsigned i = 0;i < nn.weights_ih.matrix.size();i++) {
		for (unsigned j = 0;j < nn.weights_ih.matrix[i].size();j++) {
			r = (float)rand() / RAND_MAX;
			if (r < mutationRate) {
				nn.weights_ih.matrix[i][j] = (float)rand()/RAND_MAX;
			}
		}
	}
	if (r < mutationRate) {
		nn.bias_ih = (float)rand() / RAND_MAX;

	}

	for (unsigned i = 0;i < nn.weights_ho.matrix.size();i++) {
		for (unsigned j = 0;j < nn.weights_ho.matrix[i].size();j++) {
			r = (float)rand() / RAND_MAX;
			if (r<mutationRate) {
				nn.weights_ho.matrix[i][j] = (float)rand()/RAND_MAX;
			}
		}
	}
	if (r<mutationRate) {
		nn.bias_ho = (float)rand()/RAND_MAX;

	}
}

void DNA::Update(float dt,Floor *floor) {
	float foodX = floor->foodPos.x, foodY = floor->foodPos.y;
	float snakeX = snake->body.front().position.x, snakeY = snake->body.front().position.y;
	LinkedSnake::Snake::DIRECTION snakeDir = snake->body.front().direction;
	snake->Update(dt,floor);
	if (snake->length > length) {
		fitness *= 2;
		length = snake->length;
	}
	if (foodX> snakeX&&snakeDir == LinkedSnake::Snake::DIRECTION::RIGHT|| foodX < snakeX&&snakeDir == LinkedSnake::Snake::DIRECTION::LEFT|| foodY< snakeY&&snakeDir == LinkedSnake::Snake::DIRECTION::UP|| foodY > snakeY&&snakeDir == LinkedSnake::Snake::DIRECTION::DOWN) {
		fitness += 1.f;
	}
	else{
		fitness -= 2.f;
	}
	if (fitness < 0) {
		snake->bIsDead = true;
	}
}

void DNA::Draw(sf::RenderWindow &window) {
	snake->Draw(window);
}

DNA::~DNA()
{
	delete snake;
}
