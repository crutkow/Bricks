#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"

class Brick {
public:
	Brick() : x_(0), y_(0), color_(sf::Color::Red), shape_(sf::Vector2f(BRICK_SIZE_X, BRICK_SIZE_Y)) {
		setShape();
	}

	Brick(uint x, uint y, sf::Color color) : x_(x), y_(y), color_(color), shape_(sf::Vector2f(BRICK_SIZE_X, BRICK_SIZE_Y)) {
		setShape();
	}

	Brick(uint x, uint y, sf::Color color, sf::Vector2f shape) : x_(x), y_(y), color_(color), shape_(shape) {
		setShape();
	}

	sf::RectangleShape& getShape() {
		return shape_;
	}

protected:
	void setShape();

	uint x_;
	uint y_;
	sf::Color color_;
	sf::RectangleShape shape_;
};