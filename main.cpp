// Snek.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Snake.h"
#include "Floor.h"
#include "NeuralNetwork.h"
#include "Population.h"

float getAngle(sf::Vector2f, sf::Vector2f);
float getDistance(sf::Vector2f, sf::Vector2f);

int main()
{
	srand(time(0));

	Floor floor((sf::Vector2f(800, 800)));

	//Neural Network
	const int population_size = 100;
	Population population(6,8,3,population_size);


	//Creates Window
	sf::RenderWindow window(sf::VideoMode(800, 800), "Snek");

	//Window Settings
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(10);
	window.setVerticalSyncEnabled(true);

	//Window Variables
	sf::Event event;
	sf::Clock fpsClock, gameClock;
	
	float dt; //Delta Time

	while (window.isOpen()) {
		for (unsigned alive = population_size;alive > 0;) {
			window.clear();
			floor.Update();
			floor.Draw(window);
			alive = population_size;
			for (DNA *snake : population.population) {
				if (!snake->snake->bIsDead) {
					if (!floor.food.empty()) {
						std::vector<float> inputs = {(snake->snake->bIsFoodForward(&floor))?1.f:0.f,(snake->snake->bIsFoodLeft(&floor))?1.f:0.f,(snake->snake->bIsFoodRight(&floor))?1.f:0.f,(snake->snake->bIsObjectForward())?1.f:0.f,(snake->snake->bIsObjectLeft()) ? 1.f : 0.f,(snake->snake->bIsObjectRight()) ? 1.f : 0.f };
						snake->nn.feedforward(inputs); //Feeds input into Neural Network
						std::vector<float> outputs = snake->nn.getOutput();
						unsigned max_index = 0;
						float max = 0;
						for (unsigned i = 0;i < outputs.size();i++) {
							if (outputs[i] > max) {
								max = outputs[i];
								max_index++;
							}
						}
						switch (max_index - 1) {
						case 0:
							break;
						case 1:
							switch (snake->snake->body.front().direction) {
							case LinkedSnake::Snake::DIRECTION::UP:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::LEFT;
								break;
							case LinkedSnake::Snake::DIRECTION::DOWN:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::RIGHT;
								break;
							case LinkedSnake::Snake::DIRECTION::RIGHT:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::UP;
								break;
							case LinkedSnake::Snake::DIRECTION::LEFT:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::DOWN;
								break;
							default:
								break;
							}
							break;
						case 2:
							switch (snake->snake->body.front().direction) {
							case LinkedSnake::Snake::DIRECTION::UP:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::RIGHT;
								break;
							case LinkedSnake::Snake::DIRECTION::DOWN:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::LEFT;
								break;
							case LinkedSnake::Snake::DIRECTION::RIGHT:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::DOWN;
								break;
							case LinkedSnake::Snake::DIRECTION::LEFT:
								snake->snake->body.front().direction = LinkedSnake::Snake::DIRECTION::UP;
								break;
							default:
								break;
							}
							break;
						default:
							break;
						}
					}
					dt = fpsClock.restart().asSeconds();
					while (window.pollEvent(event)) {
					}
					//std::cout << gameClock.getElapsedTime().asSeconds() << std::endl;
					if (gameClock.getElapsedTime().asSeconds() > 2.f) {
						floor.spawnFood();
						gameClock.restart();
					}
					snake->Update(dt, &floor);
					snake->Draw(window);
				}
				else {
					alive--;
				}
			}
			window.display();
		}
		std::vector<DNA *> genepool;
		population.calcFitness();
		for (DNA *d : population.population) {
			genepool.push_back(d);
		}
		population.population.clear();
		for (unsigned i = 0;i < population_size-1;i++) {
			DNA *parentA = population.selectParent(genepool);
			DNA *parentB = population.selectParent(genepool);
			DNA * child = parentA->crossOver(parentB);
			child->mutate();
			population.population.push_back(child);
		}
		population.population.push_back(population.selectElite(genepool));

		std::cout << "Generation: " << ++population.generation << std::endl;
	}
	return 0;
}

float getAngle(sf::Vector2f u, sf::Vector2f v) {
	float pi = 3.14159265;
	float dot = (u.x*v.x) + (u.y*v.y);
	float magu = sqrt(pow(u.x, 2) + pow(u.y, 2));
	float magv = sqrt(pow(v.x, 2) + pow(v.y,2));
	return acos(dot / (magu*magv))*180/pi;
}

float getDistance(sf::Vector2f u, sf::Vector2f v) {
	return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2));
}
