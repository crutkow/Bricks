#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"
#include "bounding_box.hpp"

class Brick : public BoundingBox {
public:
	Brick(uint x, uint y, sf::Color color) : x_(x), y_(y), color_(color), shape_(sf::Vector2f(BRICK_SIZE_X, BRICK_SIZE_Y)), isDisabled_(false) {
		makeShape();
	}

	Brick(uint x, uint y, sf::Color color, sf::Vector2f shapeSize) : x_(x), y_(y), color_(color), shape_(shapeSize), isDisabled_(false) {
		makeShape();
	}

	~Brick() {}

	sf::RectangleShape& getShape() {
		return shape_;
	}

	sf::Vector2f getPosition() const override {
		return sf::Vector2f((float)x_, (float)y_);
	}

	sf::Vector2i getSize() const override {
		int x = (int)shape_.getSize().x;
		int y = (int)shape_.getSize().y;
		return sf::Vector2i(x, y);
	}

	sf::Vector2f getCenter() const override {
		return sf::Vector2f((float)x_ - shape_.getSize().x / 2, (float)y_ - shape_.getSize().y / 2);
	}

	void setActive(bool active) {
		isDisabled_ = !active;
	}

	bool isDisabled() const {
		return isDisabled_;
	}

protected:
	void makeShape();

	uint x_;
	uint y_;
	sf::Color color_;
	sf::RectangleShape shape_;
	bool isDisabled_;
};