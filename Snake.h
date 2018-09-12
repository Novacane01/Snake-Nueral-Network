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
		Snake &operator = (const Snake& x) {
			return *this;
		}
		sf::RectangleShape *getSnake();
		void moveUp();
		void moveRight();
		void moveDown();
		void moveLeft();
		Snake *next = nullptr;
		Snake *previous = nullptr;
		sf::RectangleShape body;
		DIRECTION direction;
		std::vector<std::pair<sf::Vector2f,DIRECTION>> turningPoints;
		static float velocity;
	};
	LinkedSnake();
	void Draw(sf::RenderWindow &) const;
	void Update(float);
	void addUnit() const;
	bool isHit(Snake *);
	Snake* getHead() const;
	Snake* getTail() const;
private:
	Snake * head = nullptr;
	mutable Snake * tail = nullptr;
};
