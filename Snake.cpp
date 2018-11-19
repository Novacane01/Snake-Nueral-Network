#include "stdafx.h"
#include "Snake.h"
#include "Floor.h"
#include <cmath>

LinkedSnake::LinkedSnake() {
	if (body.empty()) {
		Snake newUnit;
		newUnit.body.setPosition(400,400);
		newUnit.direction = Snake::DIRECTION::RIGHT;
		newUnit.position = sf::Vector2f(400/25,400/25);
		body.push_front(newUnit);
		//addUnit();
	}
}

LinkedSnake::Snake::Snake() {
	body.setSize(sf::Vector2f(20, 20));
}

bool LinkedSnake::isHit() {
	if (length > 1) {
		for (unsigned i = 1;i < length;i++) {
			if (body.front().body.getGlobalBounds().intersects(body[i].body.getGlobalBounds())) {
				std::cout << "hit" << std::endl;
				return true;
			}
		}
	}
	return false;
}
void LinkedSnake::Draw(sf::RenderWindow &window) const {
	for (Snake s : body) {
		window.draw(s.body);
	}
}

void LinkedSnake::Update(float dt,Floor *floor) {
	if (isHit()) {
		bIsDead = true;
	}
	if (!floor->food.empty()&&body.front().body.getGlobalBounds().intersects(floor->food.at(0).getGlobalBounds())) {
		floor->food.erase(floor->food.begin());
		addUnit();
	}
	move(body.front().direction);
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
	newUnit.direction = body.front().direction;
	newUnit.body.setFillColor(body.front().body.getFillColor());
	switch (body.front().direction) {
	case Snake::DIRECTION::UP: {
		newUnit.body.setPosition(Floor::grid.at(body.front().position.x).at(body.front().position.y -1).getPosition());
		break;
	}
	case Snake::DIRECTION::DOWN: {
		newUnit.body.setPosition(Floor::grid.at(body.front().position.x).at(body.front().position.y + 1).getPosition());
		break;
	}
	case Snake::DIRECTION::LEFT: {
		newUnit.body.setPosition(Floor::grid.at(body.front().position.x - 1).at(body.front().position.y).getPosition());
		break;
	}
	case Snake::DIRECTION::RIGHT: {
		newUnit.body.setPosition(Floor::grid.at(body.front().position.x + 1).at(body.front().position.y).getPosition());
		break;
	}
	default: {
		break;
	}
	}
	newUnit.position = sf::Vector2f(newUnit.body.getPosition().x / 25,newUnit.body.getPosition().y / 25);
	body.push_front(newUnit);
	length++;
}

void LinkedSnake::move(Snake::DIRECTION dir) {
	Snake newUnit;
	newUnit.body.setFillColor(body.front().body.getFillColor());
	newUnit.direction = dir;
	switch (dir) {
	case Snake::DIRECTION::UP: {
		try {
			newUnit.body.setPosition(Floor::grid.at(body.front().position.x).at(body.front().position.y-1).getPosition());
		}
		catch (std::out_of_range) {
			bIsDead = true;
		}
		break;
	}
	case Snake::DIRECTION::DOWN: {
		try {
			newUnit.body.setPosition(Floor::grid.at(body.front().position.x).at(body.front().position.y+1).getPosition());
		}
		catch (std::out_of_range) {
			bIsDead = true;
		}		
		break;
	}
	case Snake::DIRECTION::LEFT: {
		try {
			newUnit.body.setPosition(Floor::grid.at(body.front().position.x-1).at(body.front().position.y).getPosition());
		}
		catch (std::out_of_range) {
			bIsDead = true;
		}		
		break;
	}
	case Snake::DIRECTION::RIGHT: {
		try {
			newUnit.body.setPosition(Floor::grid.at(body.front().position.x+1).at(body.front().position.y).getPosition());
		}
		catch (std::out_of_range) {
			bIsDead = true;
		}		
		break;
	}
	default: {
		break;
	}
	}
	if (bIsDead) {
		return;
	}
	newUnit.position = sf::Vector2f(newUnit.body.getPosition().x/25, newUnit.body.getPosition().y / 25);
	body.push_front(newUnit);
	body.pop_back();
}


bool LinkedSnake::bIsObjectLeft() {
	switch(body.front().direction) {
	case Snake::DIRECTION::UP:
		for (Snake s : body) {
			if (s.position.x == body.front().position.x - 1 || s.position.x - 1 < 0) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::DOWN:
		for (Snake s : body) {
			if (s.position.x == body.front().position.x + 1 || s.position.x + 1 > 32) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::RIGHT:
		for (Snake s : body) {
			if (s.position.y == body.front().position.y - 1 || s.position.y - 1 < 0) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::LEFT:
		for (Snake s : body) {
			if (s.position.y == body.front().position.y + 1 || s.position.y + 1 > 32) {
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
bool LinkedSnake::bIsObjectRight() {
	switch (body.front().direction) {
	case Snake::DIRECTION::UP:
		for (Snake s : body) {
			if (s.position.x == body.front().position.x + 1 || s.position.x + 1 > 32) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::DOWN:
		for (Snake s : body) {
			if (s.position.x == body.front().position.x - 1 || s.position.x - 1 < 0) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::RIGHT:
		for (Snake s : body) {
			if (s.position.y == body.front().position.y + 1 || s.position.y + 1 >32) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::LEFT:
		for (Snake s : body) {
			if (s.position.y == body.front().position.y - 1 || s.position.y - 1 <0) {
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
bool LinkedSnake::bIsObjectForward() {
	switch (body.front().direction) {
	case Snake::DIRECTION::UP:
		for (Snake s : body) {
			if (s.position.y == body.front().position.y - 1 || s.position.y - 1 < 0) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::DOWN:
		for (Snake s : body) {
			if (s.position.y == body.front().position.y + 1 || s.position.y + 1 > 32) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::LEFT:
		for (Snake s : body) {
			if (s.position.x == body.front().position.x - 1 || s.position.x - 1 < 0) {
				return true;
			}
		}
		break;
	case Snake::DIRECTION::RIGHT:
		for (Snake s : body) {
			if (s.position.x == body.front().position.x + 1 || s.position.x + 1 > 32) {
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
bool LinkedSnake::bIsFoodForward(Floor *floor) {
	switch (body.front().direction) {
	case Snake::DIRECTION::UP:
		if (floor->foodPos.y<body.front().position.y) {
			return true;
		}
		break;
	case Snake::DIRECTION::DOWN:
		if (floor->foodPos.y>body.front().position.y) {
			return true;
		}
		break;
	case Snake::DIRECTION::LEFT:
		if (floor->foodPos.x<body.front().position.x) {
			return true;
		}
		break;
	case Snake::DIRECTION::RIGHT:
		if (floor->foodPos.x>body.front().position.x) {
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}
bool LinkedSnake::bIsFoodLeft(Floor *floor) {
	switch (body.front().direction) {
	case Snake::DIRECTION::UP:
		if (floor->foodPos.x<body.front().position.x) {
			return true;
		}
		break;
	case Snake::DIRECTION::DOWN:
		if (floor->foodPos.x>body.front().position.x) {
			return true;
		}
		break;
	case Snake::DIRECTION::LEFT:
		if (floor->foodPos.y>body.front().position.y) {
			return true;
		}
		break;
	case Snake::DIRECTION::RIGHT:
		if (floor->foodPos.y<body.front().position.y) {
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}
bool LinkedSnake::bIsFoodRight(Floor *floor) {
	switch (body.front().direction) {
	case Snake::DIRECTION::UP:
		if (floor->foodPos.x>body.front().position.x) {
			return true;
		}
		break;
	case Snake::DIRECTION::DOWN:
		if (floor->foodPos.x<body.front().position.x) {
			return true;
		}
		break;
	case Snake::DIRECTION::LEFT:
		if (floor->foodPos.y<body.front().position.y) {
			return true;
		}
		break;
	case Snake::DIRECTION::RIGHT:
		if (floor->foodPos.y>body.front().position.y) {
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}