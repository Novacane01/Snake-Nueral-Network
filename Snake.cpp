#include "stdafx.h"
#include "Snake.h"
#include "Floor.h"
#include <cmath>


float getDistance(sf::Vector2f, sf::Vector2f);

LinkedSnake::LinkedSnake() {
	if (snake.empty()) {
		Snake newUnit;
		newUnit.body.setPosition(0,0);
		newUnit.direction = Snake::DIRECTION::RIGHT;
		snake.push_back(newUnit);
	}
}

LinkedSnake::Snake::Snake() {
	body.setSize(sf::Vector2f(20, 20));
}

bool LinkedSnake::isHit(Snake *snake) {
	if (snake[0].body.getGlobalBounds().intersects(snake->body.getGlobalBounds())) {
		return true;
	}
	return false;
}
void LinkedSnake::Draw(sf::RenderWindow &window) const {
	for (Snake s : snake) {
		window.draw(s.body);
	}
}

void LinkedSnake::Update(float dt,Floor *floor) {
	if (!floor->food.empty()&&snake[0].body.getGlobalBounds().intersects(floor->food.at(0).getGlobalBounds())) {
		floor->food.erase(floor->food.begin());
		addUnit();
	}
	move(snake[0].direction);
}

sf::RectangleShape* LinkedSnake::Snake::getSnake(){
	return &body;
}

void LinkedSnake::Snake::moveDown() {
	if (direction == DIRECTION::UP) {
		return;
	}
	direction = DIRECTION::DOWN;
}

void LinkedSnake::Snake::moveUp() {
	if (direction == DIRECTION::DOWN) {
		return;
	}
	direction = DIRECTION::UP;

}

void LinkedSnake::Snake::moveLeft() {
	if (direction == DIRECTION::RIGHT) {
		return;
	}
	direction = DIRECTION::LEFT;
}

void LinkedSnake::Snake::moveRight() {
	if (direction == DIRECTION::LEFT) {
		return;
	}
	direction = DIRECTION::RIGHT;
}

//Adds unit directly behind tail
void LinkedSnake::addUnit() {
	Snake newUnit;
	newUnit.direction = snake.back().direction;
	switch (snake.back().direction) {
	case Snake::DIRECTION::UP: {
		newUnit.body.setPosition(snake.back().body.getPosition().x, snake.back().body.getPosition().y - 25);
		break;
	}
	case Snake::DIRECTION::DOWN: {
		newUnit.body.setPosition(snake.back().body.getPosition().x, snake.back().body.getPosition().y + 25);
		break;
	}
	case Snake::DIRECTION::LEFT: {
		newUnit.body.setPosition(snake.back().body.getPosition().x - 25, snake.back().body.getPosition().y);
		break;
	}
	case Snake::DIRECTION::RIGHT: {
		newUnit.body.setPosition(snake.back().body.getPosition().x + 25, snake.back().body.getPosition().y);
		break;
	}
	default: {
		break;
	}
	}
	snake.push_back(newUnit);
}

float getDistance(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

void LinkedSnake::move(Snake::DIRECTION dir) {
	Snake newUnit;
	newUnit.id++;
	newUnit.direction = dir;
	switch (dir) {
	case Snake::DIRECTION::UP: {
		newUnit.body.setPosition(snake[0].body.getPosition().x, snake[0].body.getPosition().y - 25);
		break;
	}
	case Snake::DIRECTION::DOWN: {
		newUnit.body.setPosition(snake[0].body.getPosition().x, snake[0].body.getPosition().y + 25);
		break;
	}
	case Snake::DIRECTION::LEFT: {
		newUnit.body.setPosition(snake[0].body.getPosition().x - 25, snake[0].body.getPosition().y);
		break;
	}
	case Snake::DIRECTION::RIGHT: {
		newUnit.body.setPosition(snake[0].body.getPosition().x + 25, snake[0].body.getPosition().y);
		break;
	}
	default: {
		break;
	}
	}
	snake.insert(snake.begin(), newUnit);
	snake.pop_back();
	
}
