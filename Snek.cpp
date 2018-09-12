// Snek.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Snake.h"
#include "Floor.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Snek");
	LinkedSnake snake;
	Floor floor((sf::Vector2f(1920,1080)));
	sf::Event event;
	sf::Clock fpsClock, gameClock;
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	float dt;
	while (window.isOpen()) {
		dt = fpsClock.restart().asSeconds();
		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::W) {
				snake.getHead()->moveUp();
			}
			else if (event.key.code == sf::Keyboard::S) {
				snake.getHead()->moveDown();
			}
			else if (event.key.code == sf::Keyboard::D) {
				snake.getHead()->moveRight();
			}
			else if (event.key.code == sf::Keyboard::A) {
				snake.getHead()->moveLeft();
			}
		}
		//std::cout << gameClock.getElapsedTime().asSeconds() << std::endl;
		if (gameClock.getElapsedTime().asSeconds() > 2.f) {
			floor.spawnFood();
			gameClock.restart();
		}
		window.clear();
		floor.Update();
		floor.Draw(window);
		snake.Update(dt);
		snake.Draw(window);
		window.display();
	}
	return 0;
}

