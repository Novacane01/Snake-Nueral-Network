#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include <cstdlib>

class Floor {
public:
	Floor(sf::Vector2f);
	sf::RectangleShape& getFloor();
	std::vector<sf::RectangleShape> food;
	void Update();
	void Draw(sf::RenderWindow &);
	void spawnFood();
private:
	std::vector<std::vector<sf::RectangleShape>> grid;
	std::vector<sf::RectangleShape> walls;
	const sf::Vector2f size;
};

