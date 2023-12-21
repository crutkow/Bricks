#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"
#include "bounding_box.hpp"

class Ball : public BoundingBox {
public:
	Ball(uint x, uint y) : x_(x), y_(y), color_(sf::Color::White), shape_(BALL_RADIUS), 
		isMoving_(false), movePosition_(sf::Vector2f((float)x, (float)y)), moveDirection_(sf::Vector2f(0, 0)) {
		setShape();
	}

	sf::CircleShape& getShape() {
		return shape_;
	}

	void move(sf::Vector2f direction);

	void bounce(NormalDirections normal);

	void stop();

	void update(sf::Time deltaTime);

	sf::Vector2f getPosition() override {
		return sf::Vector2f((float)x_, (float)y_);
	}

	sf::Vector2i getSize() override {
		return sf::Vector2i(BALL_RADIUS * 2, BALL_RADIUS * 2);
	}

	sf::Vector2f getCenter() override {
		return sf::Vector2f((float)x_ + BALL_RADIUS / 2, (float)y_ + BALL_RADIUS / 2);
	}

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