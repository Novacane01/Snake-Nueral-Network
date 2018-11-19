#include "stdafx.h"
#include "Floor.h"

std::vector<std::vector<sf::RectangleShape>> Floor::grid;

Floor::Floor(sf::Vector2f size) :size(size) {
	grid.resize(size.x/25);
	for (unsigned i = 0;i < grid.size();i++) {
		grid[i].resize(size.y / 25);
	}
	for (unsigned i = 0;i < size.x / 25; i++) {
		for (unsigned j = 0;j < size.y / 25;j++) {
			grid[i][j].setPosition(25 * i, 25 * j);
			grid[i][j].setSize(sf::Vector2f(20, 20));
			grid[i][j].setFillColor(sf::Color::Green);
		}
	}
	spawnFood();
}


void Floor::Update() {
	if (food.size() == 0) {
		spawnFood();
	}
}

void Floor::spawnFood() {
	if (food.empty()) {
		sf::RectangleShape pill(sf::Vector2f(20,20));
		foodPos = sf::Vector2f((rand() % 32), (rand() % 32));
		pill.setPosition(sf::Vector2f(foodPos.x*25,foodPos.y*25));
		food.push_back(pill);
	}
}

//sf::RectangleShape& Floor::getFloor(){
//	//return ;
//}

void Floor::Draw(sf::RenderWindow &window) {
	for (std::vector<sf::RectangleShape> x : grid) {
		for (sf::RectangleShape y : x) {
			window.draw(y);
		}
	}
	for (sf::RectangleShape c : food) {
		window.draw(c);
	}
}