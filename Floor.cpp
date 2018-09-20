#include "stdafx.h"
#include "Floor.h"

Floor::Floor(sf::Vector2f size) :size(size), grid(size.x/20, std::vector<sf::RectangleShape>(size.y/20)) {
	for (unsigned i = 0;i < size.x/20; i++) {
		for (unsigned j = 0;j < size.y/20;j++) {
			grid[i][j].setPosition(25*i, 25*j);
			grid[i][j].setSize(sf::Vector2f(20, 20));
			//grid[i][j].setFillColor(sf::Color::Green);
		}
	}
	srand(time(0));
}


void Floor::Update() {
	if (food.size() == 0) {
		spawnFood();
	}
}

void Floor::spawnFood() {
	if (food.empty()) {
		sf::RectangleShape pill(sf::Vector2f(20,20));
		pill.setPosition((rand()%32)*25, (rand()%32)*25);
		food.push_back(pill);
	}
}

//sf::RectangleShape& Floor::getFloor(){
//	//return ;
//}

void Floor::Draw(sf::RenderWindow &window) {
	/*for (std::vector<sf::RectangleShape> x : grid) {
		for (sf::RectangleShape y : x) {
			window.draw(y);
		}
	}*/
	for (sf::RectangleShape c : food) {
		window.draw(c);
	}
}