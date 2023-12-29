#include <iostream>
#include <cmath>

#include "drop.hpp"

void Drop::makeCircleShapes() {
	for (int i = 0; i < DROP_CIRCLE_COUNT; ++i) {
		circleShapes_[i].setFillColor(sf::Color::Black);
		circleShapes_[i].setPosition((float)x_ + circleShapesOffsets_[i].x, moveY_ + circleShapesOffsets_[i].y);
	}
}

void Drop::update(sf::Time deltaTime) {
	float deltaMove = DROP_MOVE_SPEED * deltaTime.asSeconds() * FRAME_RATE;

	moveY_ += deltaMove;
	y_ = (uint)moveY_;

	shape_.setPosition((float)x_, moveY_);

	for (int i = 0; i < DROP_CIRCLE_COUNT; ++i) {
		float x = circleShapes_[i].getPosition().x;
		circleShapes_[i].setPosition(x, moveY_ + circleShapesOffsets_[i].y);
	}
}