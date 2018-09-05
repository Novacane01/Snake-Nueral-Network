// Snek.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Snake.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Snek");
	Snake snake;
	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::W) {
				snake.moveUp();
			}
			else if (event.key.code == sf::Keyboard::S) {
				snake.moveDown()
			}
		}
		window.clear();
		snake.Draw(window);
		window.display();
	}
	return 0;
}

