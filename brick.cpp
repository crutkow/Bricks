#include "brick.hpp"

void Brick::setShape() {
	shape_.setFillColor(color_);
	//shape_.setOutlineThickness(10.f);
	//shape_.setOutlineColor(sf::Color::White);

	shape_.setPosition(x_, y_);
}