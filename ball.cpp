#include "ball.hpp"

void Ball::setShape() {
	shape_.setFillColor(color_);
	shape_.setPosition(x_, y_);
}