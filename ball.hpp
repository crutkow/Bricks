#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"

class Ball {
public:
	Ball(uint x, uint y) : x_(x), y_(y), color_(sf::Color::White), shape_(BALL_RADIUS) {
		setShape();
	}

	sf::CircleShape& getShape() {
		return shape_;
	}

protected:
	void setShape();

	uint x_;
	uint y_;
	sf::Color color_;
	sf::CircleShape shape_;
};