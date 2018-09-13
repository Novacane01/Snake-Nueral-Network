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
	window.setFramerateLimit(10);
	window.setVerticalSyncEnabled(true);
	float dt;
	while (window.isOpen()) {
		dt = fpsClock.restart().asSeconds();
		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::W) {
				snake.snake[0].moveUp();
			}
			else if (event.key.code == sf::Keyboard::S) {
				snake.snake[0].moveDown();
			}
			else if (event.key.code == sf::Keyboard::D) {
				snake.snake[0].moveRight();
			}
			else if (event.key.code == sf::Keyboard::A) {
				snake.snake[0].moveLeft();
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

