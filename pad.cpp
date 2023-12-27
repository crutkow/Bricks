#include <iostream>
#include <cmath>

#include "pad.hpp"

void Pad::move(int targetX) {
	if (targetX < BOARD_BOUND_SIZE_X + PAD_SIZE_X / 2 || targetX > BOARD_SIZE_X - BOARD_BOUND_SIZE_X - 1 - PAD_SIZE_X / 2) return;

	targetMoveX_ = targetX - PAD_SIZE_X / 2;
	isMovingToTarget_ = true;
}

void Pad::update(sf::Time deltaTime) {
	if (isMovingToTarget_) {
		float moveDistance = abs((float)targetMoveX_ - moveX_);
		int moveSign = (float)targetMoveX_ - moveX_ < 0 ? -1 : 1;
		float deltaMove = PAD_MOVE_SPEED * deltaTime.asSeconds() * FRAME_RATE;

		if (moveDistance <= deltaMove) {
			moveX_ = (float)targetMoveX_;
			isMovingToTarget_ = false;
		}
		else {
			moveX_ += deltaMove * moveSign;
		}
		x_ = (uint)(moveX_);

		shape_.setPosition(moveX_, (float)y_);
	}
}