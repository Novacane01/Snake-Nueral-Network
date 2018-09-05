#include "stdafx.h"
#include "Snake.h"
#include "Floor.h"

Snake::Snake() {
	body = new std::vector<sf::RectangleShape>;
	body->push_back(sf::RectangleShape(sf::Vector2f(20,20)));
	body->at(0).setPosition(1920/2, 1080/2);
}

void Snake::Draw(sf::RenderWindow &window) {
	for (int i = 0;i < body->size();i++) {
		window.draw(body->at(i));
	}
}

void Snake::Update() {
	if (body->at(0).getGlobalBounds().intersects(Floor::food.at(0).getGlobalBounds())) {
		Floor::food.erase(Floor::food.begin());
		Floor::spawnFood();
	}
}