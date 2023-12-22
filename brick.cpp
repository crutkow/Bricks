#include "brick.hpp"

void Brick::makeShape() {
	shape_.setFillColor(color_);
	shape_.setPosition((float)x_, (float)y_);
}