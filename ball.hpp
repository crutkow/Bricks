#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"
#include "bounding_box.hpp"

class Ball : public BoundingBox {
public:
	Ball(uint x, uint y) : color_(sf::Color::White), shape_(BALL_RADIUS), 
		isMoving_(false), movePosition_(sf::Vector2f((float)x, (float)y)), moveDirection_(sf::Vector2f(0, 0)),
		isMovingHorizontaly_(true) {
		makeShape();
	}

	sf::CircleShape& getShape() {
		return shape_;
	}

	sf::Vector2f getPosition() const override {
		return movePosition_;
	}

	sf::Vector2i getSize() const override {
		return sf::Vector2i(BALL_RADIUS * 2, BALL_RADIUS * 2);
	}

	sf::Vector2f getCenter() const override {
		return sf::Vector2f((float)movePosition_.x + BALL_RADIUS, (float)movePosition_.y + BALL_RADIUS);
	}

	void move(sf::Vector2f direction);

	void bounce(NormalDirections normal);

	void stop();

	void setMoveHorizontaly(float x);

	void moveHorizontaly(float x);

	void update(sf::Time deltaTime);

	bool isMoving() const {
		return isMoving_;
	}

	bool isMovingHorizontaly() const {
		return isMovingHorizontaly_;
	}

protected:
	void makeShape();

	sf::Color color_;
	sf::CircleShape shape_;
	bool isMoving_;
	sf::Vector2f movePosition_;
	sf::Vector2f moveDirection_;
	bool isMovingHorizontaly_;
};