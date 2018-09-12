#include "stdafx.h"
#include "Floor.h"

sf::RectangleShape Floor::body;
std::vector<sf::CircleShape> Floor::food;


Floor::Floor(sf::Vector2f size) {
	body.setSize(size);
	body.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	body.setOutlineColor(sf::Color::Red);
	srand(time(0));
}

void Floor::Update() {
	if (food.size() == 0) {
		spawnFood();
	}
}

void Floor::spawnFood() {
	if (food.empty()) {
		sf::CircleShape pill(20);
		pill.setPosition(rand()%1920 - 20, rand()%1080-20);
		food.push_back(pill);
	}
}

sf::RectangleShape& Floor::getFloor(){
	return body;
}

void Floor::Draw(sf::RenderWindow &window) {
	for (sf::CircleShape c : food) {
		window.draw(c);
	}
}