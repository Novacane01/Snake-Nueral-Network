#include "stdafx.h"
#include "Floor.h"

sf::RectangleShape Floor::body;
std::vector<sf::CircleShape> Floor::food;

Floor::Floor(sf::Vector2f size) {
	body.setSize(size);
	body.setPosition(sf::Vector2f(1920 / 2, 1080 / 2));
	body.setOutlineColor(sf::Color::Red);
}

void Floor::Update() {
	if (food.size() == 0) {
		spawnFood();
	}
}

void Floor::spawnFood() {
	sf::CircleShape pill(20);
	pill.setPosition(pill.getPosition().x + 20, pill.getPosition().y);
	food.push_back(sf::CircleShape(10));
}

sf::RectangleShape& Floor::getFloor(){
	return body;
}