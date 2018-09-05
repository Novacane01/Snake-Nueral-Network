#include "stdafx.h"
#include "Snake.h"
#include "Floor.h"

Snake::Snake() {
	body.setSize(sf::Vector2f(20, 20));
	snake_vector.push_back(new Snake());
	snake_vector[0]->getSnake()->setPosition(1920 / 2, 1080 / 2);
}

void Snake::Draw(sf::RenderWindow &window) {
	for (int i = 0;i < snake_vector.size();i++) {
		window.draw(snake_vector.at(0)->body);
	}
}

void Snake::Update() {
	if (snake_vector.at(0)->body.getGlobalBounds().intersects(Floor::food.at(0).getGlobalBounds())) {
		Floor::food.erase(Floor::food.begin());
		Floor::spawnFood();
	}
}

sf::RectangleShape* Snake::getSnake(){
	return &body;
}

void Snake::moveDown() {
	body.move(0, 1);
}

void Snake::moveUp() {
	body.move(0, -1);
}

void Snake::moveLeft() {
	body.move(-1, 0);
}

void Snake::moveRight() {
	body.move(-1, 0);
}