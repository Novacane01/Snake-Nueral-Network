#include "stdafx.h"
#include "Snake.h"
#include "Floor.h"
#include <cmath>

float LinkedSnake::Snake::velocity = 80.f;
float getDistance(sf::Vector2f, sf::Vector2f);

LinkedSnake::LinkedSnake() {
	if (head == nullptr&&tail==nullptr) {
		head = new Snake();
		head->previous = head;
		tail = head;
		head->body.setPosition(1920 / 2, 1080 / 2);
		head->direction = Snake::DIRECTION::UP;
	}
}

LinkedSnake::Snake::Snake() {
	body.setSize(sf::Vector2f(20, 20));
}

bool LinkedSnake::isHit(Snake *snake) {
	if (head->body.getGlobalBounds().intersects(snake->body.getGlobalBounds())) {
		return true;
	}
	return false;
}
void LinkedSnake::Draw(sf::RenderWindow &window) const {
	Snake *current = head;
	if (current == head) {
		window.draw(head->body);
	}
	while(current!=nullptr) {
		window.draw(current->body);
		current = current->next;
	}
}

void LinkedSnake::Update(float dt) {
	if (!Floor::food.empty()&&head->body.getGlobalBounds().intersects(Floor::food.at(0).getGlobalBounds())) {
		Floor::food.erase(Floor::food.begin());
		addUnit();
	}
	Snake *current = head;
	while (current!= nullptr) {
		if (current != head) {
			if (isHit(current)) {
				//return;
			}
			for (std::pair<sf::Vector2f, Snake::DIRECTION> x : head->turningPoints) {
				if (x.first == current->body.getPosition()) {
					current->direction = x.second;
					if (current == tail) {
						head->turningPoints.erase(head->turningPoints.begin());
					}
				}
			}
		}
		switch (current->direction) {
			case Snake::DIRECTION::UP: {
				current->body.move(0, -20);
				break;
			}
			case Snake::DIRECTION::DOWN: {
				current->body.move(0, 20);
				break;
			}
			case Snake::DIRECTION::LEFT: {
				current->body.move(-20, 0);
				break;
			}
			case Snake::DIRECTION::RIGHT: {
				current->body.move(20, 0);
				break;
			}
			default: {
				break;
			}
		}
		current = current->next;
	}
}

sf::RectangleShape* LinkedSnake::Snake::getSnake(){
	return &body;
}

void LinkedSnake::Snake::moveDown() {
	direction = DIRECTION::DOWN;
	turningPoints.push_back(std::pair<sf::Vector2f, DIRECTION>(body.getPosition(), direction));
}

void LinkedSnake::Snake::moveUp() {
	direction = DIRECTION::UP;
	turningPoints.push_back(std::pair<sf::Vector2f, DIRECTION>(body.getPosition(), direction));

}

void LinkedSnake::Snake::moveLeft() {
	direction = DIRECTION::LEFT;
	turningPoints.push_back(std::pair<sf::Vector2f, DIRECTION>(body.getPosition(), direction));

}

void LinkedSnake::Snake::moveRight() {
	direction = DIRECTION::RIGHT;
	turningPoints.push_back(std::pair<sf::Vector2f, DIRECTION>(body.getPosition(), direction));

}

//Adds unit directly behind tail
void LinkedSnake::addUnit() const {
	Snake *newUnit = new Snake();
	newUnit->body.setPosition(tail->body.getPosition());
	newUnit->direction = tail->direction;
	switch (newUnit->direction) {
		case Snake::DIRECTION::UP: {
				newUnit->body.move(0, 20);
				break;
			}
		case Snake::DIRECTION::DOWN: {
				newUnit->body.move(0, -20);
				break;
			}
		case Snake::DIRECTION::LEFT: {
				newUnit->body.move(20, 0);
				break;
			}
		case Snake::DIRECTION::RIGHT: {
				newUnit->body.move(-20, 0);
				break;
			}
		default: {
			break;
		}
	}
	tail->next = newUnit;
	newUnit->previous = tail;
	tail = newUnit;
}

LinkedSnake::Snake* LinkedSnake::getHead() const {
	return head;
}

LinkedSnake::Snake* LinkedSnake::getTail() const {
	return tail;
}

float getDistance(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}