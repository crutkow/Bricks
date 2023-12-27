#include "brick.hpp"

void Brick::makeShape() {
	shape_.setFillColor(color_);
	shape_.setPosition((float)x_, (float)y_);

	shape_.setOutlineThickness(-BRICK_OUTLINE_SIZE);
	shape_.setOutlineColor(sf::Color(0, 0, 0));
}