#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"
#include "brick.hpp"

class Drop : public Brick {
public:
	Drop(uint x, uint y) : Brick(x, y, sf::Color::Cyan, sf::Vector2f(DROP_SIZE_X, DROP_SIZE_Y)), moveY_((float)y),
		circleShapes_{ sf::CircleShape(DROP_CIRCLE_RADIUS), sf::CircleShape(DROP_CIRCLE_RADIUS), sf::CircleShape(DROP_CIRCLE_RADIUS) },
		circleShapesOffsets_{ sf::Vector2f(3.0f, 19.0f), sf::Vector2f(12.0f, 4.0f), sf::Vector2f(21.0f, 19.0f) } {
		makeCircleShapes();
	}

	~Drop() {}

	sf::Vector2f getPosition() const override {
		return sf::Vector2f((float)x_, moveY_);
	}

	sf::Vector2f getCenter() const override {
		return sf::Vector2f((float)x_ + shape_.getSize().x / 2, moveY_ + shape_.getSize().y / 2);
	}

	sf::CircleShape& getCircleShape(int index) {
		return circleShapes_[index];
	}

	void update(sf::Time deltaTime);

protected:
	void makeCircleShapes();

	float moveY_;
	sf::CircleShape circleShapes_[DROP_CIRCLE_COUNT];
	sf::Vector2f circleShapesOffsets_[DROP_CIRCLE_COUNT];
};