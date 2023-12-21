#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"
#include "bounding_box.hpp"

class Brick : public BoundingBox {
public:
	Brick() : x_(0), y_(0), color_(sf::Color::Red), shape_(sf::Vector2f(BRICK_SIZE_X, BRICK_SIZE_Y)), isDisabled_(false) {
		setShape();
	}

	Brick(uint x, uint y, sf::Color color) : x_(x), y_(y), color_(color), shape_(sf::Vector2f(BRICK_SIZE_X, BRICK_SIZE_Y)), isDisabled_(false) {
		setShape();
	}

	Brick(uint x, uint y, sf::Color color, sf::Vector2f shape) : x_(x), y_(y), color_(color), shape_(shape), isDisabled_(false) {
		setShape();
	}

	sf::RectangleShape& getShape() {
		return shape_;
	}

	sf::Vector2f getPosition() override {
		return sf::Vector2f((float)x_, (float)y_);
	}

	sf::Vector2i getSize() override {
		int x = (int)shape_.getSize().x;
		int y = (int)shape_.getSize().y;
		return sf::Vector2i(x, y);
	}

	sf::Vector2f getCenter() override {
		return sf::Vector2f((float)x_ - shape_.getSize().x / 2, (float)y_ - shape_.getSize().y / 2);
	}

	void disable() {
		isDisabled_ = true;
	}

	bool isDisabled() {
		return isDisabled_;
	}

protected:
	void setShape();

	uint x_;
	uint y_;
	sf::Color color_;
	sf::RectangleShape shape_;
	bool isDisabled_;
};