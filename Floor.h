#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class Floor {
public:
	Floor(sf::Vector2f);
	static sf::RectangleShape& getFloor();
	static std::vector<sf::CircleShape> food;
	static void Update();
	static void Draw(sf::RenderWindow &);
	static void spawnFood();
private:
	static sf::RectangleShape body;
};