#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"
#include "brick.hpp"

class Pad : public Brick {
public:
	Pad(uint x, uint y) : Brick(x, y, sf::Color::Blue, sf::Vector2f(PAD_SIZE_X, PAD_SIZE_Y)), 
		isMovingToTarget_(false), targetMoveX_(0), moveX_((float)x) {
	}

	sf::Vector2f getPosition() const override {
		return sf::Vector2f(moveX_, (float)y_);
	}

	sf::Vector2f getCenter() const override {
		return sf::Vector2f(moveX_ + shape_.getSize().x / 2, (float)y_ + shape_.getSize().y / 2);
	}

	void move(int targetX);

	void update(sf::Time deltaTime);

protected:
	bool isMovingToTarget_;
	uint targetMoveX_;
	float moveX_;
};