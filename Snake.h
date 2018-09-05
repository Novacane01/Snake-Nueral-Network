#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

class Snake {
public:
	enum class DIRECTION{UP,RIGHT,DOWN,LEFT};
	Snake();
	std::vector<sf::RectangleShape> *getSnake();
	void Update();
	void Draw(sf::RenderWindow &);
	void addUnit();
private:
	std::vector<sf::RectangleShape> *body;
	float velocity;
};
