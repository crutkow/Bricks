#include <cmath>

#include "ball.hpp"

void Ball::setShape() {
	shape_.setFillColor(color_);
	shape_.setPosition((float)x_, (float)y_);
}

void Ball::move(sf::Vector2f direction) {
	moveDirection_ = direction;
	isMoving_ = true;
}

void Ball::bounce(NormalDirections normal) {
	switch (normal) {
	case NormalDirections::Up:
		moveDirection_.y = -abs(moveDirection_.y);
		break;
	case NormalDirections::Down:
		moveDirection_.y = abs(moveDirection_.y);
		break;
	case NormalDirections::Left:
		moveDirection_.x = -abs(moveDirection_.x);
		break;
	case NormalDirections::Right:
		moveDirection_.x = abs(moveDirection_.x);
		break;
	}
}

void Ball::stop() {
	isMoving_ = false;
}

void Ball::update(sf::Time deltaTime) {
	if (isMoving_) {
		sf::Vector2f delta(moveDirection_.x * BALL_MOVE_SPEED * deltaTime.asSeconds() * FRAME_RATE,
			moveDirection_.y * BALL_MOVE_SPEED * deltaTime.asSeconds() * FRAME_RATE);

		movePosition_ += delta;

		x_ = (uint)(movePosition_.x);
		y_ = (uint)(movePosition_.y);

		shape_.setPosition(movePosition_.x, movePosition_.y);
	}
}