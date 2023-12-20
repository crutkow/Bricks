#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"

class Ball {
public:
	Ball(uint x, uint y) : x_(x), y_(y), color_(sf::Color::White), shape_(BALL_RADIUS), 
		isMoving_(false), movePosition_(sf::Vector2f(x, y)), moveDirection_(sf::Vector2f(0, 0)) {
		setShape();
	}

	sf::CircleShape& getShape() {
		return shape_;
	}

	void bounce(sf::Vector2f direction);

	void stop();

	void update(sf::Time deltaTime);

protected:
	void setShape();

	uint x_;
	uint y_;
	sf::Color color_;
	sf::CircleShape shape_;
	bool isMoving_;
	sf::Vector2f movePosition_;
	sf::Vector2f moveDirection_;
};