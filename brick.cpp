#include "brick.hpp"

void Brick::makeShape() {
	shape_.setFillColor(color_);
	//shape_.setOutlineThickness(10.f);
	//shape_.setOutlineColor(sf::Color::White);

	shape_.setPosition((float)x_, (float)y_);
}