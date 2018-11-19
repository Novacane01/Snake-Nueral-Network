#pragma once
#include <deque>
#include <iostream>
#include "Floor.h"
#include "SFML\Graphics.hpp"

class LinkedSnake{
public:
	struct Snake {
	public:
		enum class DIRECTION { UP, RIGHT, DOWN, LEFT };
		Snake();
		void moveUp();
		void moveRight();
		void moveDown();
		void moveLeft();
		sf::RectangleShape body;
		DIRECTION direction = DIRECTION::UP;
		sf::Vector2f position;
	};
	LinkedSnake();
	void Draw(sf::RenderWindow &) const;
	void Update(float, Floor *);
	void addUnit();
	bool isHit();
	bool bIsObjectLeft();
	bool bIsObjectRight();
	bool bIsObjectForward();
	bool bIsFoodLeft(Floor *);
	bool bIsFoodRight(Floor *);
	bool bIsFoodForward(Floor *);
	void move(Snake::DIRECTION);
	std::deque<Snake> body;
	bool bIsDead = false;
	unsigned length = 1;

};
