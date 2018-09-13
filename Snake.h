#pragma once
#include <vector>
#include <iostream>
#include "SFML\Graphics.hpp"

class LinkedSnake{
public:
	struct Snake {
	public:
		enum class DIRECTION { UP, RIGHT, DOWN, LEFT };
		Snake();
		sf::RectangleShape *getSnake();
		void moveUp();
		void moveRight();
		void moveDown();
		void moveLeft();
		sf::RectangleShape body;
		DIRECTION direction = DIRECTION::UP;
		std::vector<std::pair<sf::Vector2f,DIRECTION>> turningPoints;
		static float velocity;
		int id=0;
	};
	LinkedSnake();
	void Draw(sf::RenderWindow &) const;
	void Update(float);
	void addUnit();
	bool isHit(Snake *);
	void move(Snake::DIRECTION);
	Snake getHead() const;
	Snake* getTail() const;
	std::vector<Snake> snake;
};
