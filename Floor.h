#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include <cstdlib>

class Floor {
public:
	Floor(sf::Vector2f);
	std::vector<sf::RectangleShape> food;
	void Update();
	void Draw(sf::RenderWindow &);
	void spawnFood();
	static std::vector<std::vector<sf::RectangleShape>> grid;
	sf::Vector2f foodPos;
private:
	std::vector<sf::RectangleShape> walls;
	const sf::Vector2f size;
};

