#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

class Snake {
public:
	enum class DIRECTION{UP,RIGHT,DOWN,LEFT};
	Snake();
	sf::RectangleShape *getSnake();
	void Update();
	void Draw(sf::RenderWindow &);
	void addUnit();
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
private:
	static std::vector<Snake*> snake_vector;
	sf::RectangleShape body;
	float velocity;
};
