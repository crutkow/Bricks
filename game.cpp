#include <iostream>
#include "game.hpp"


void Game::start() {
	sf::Color colors[] = { sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green };
	const int colorCount = 4;
	int nextColor = 0;

	bricks_.clear();

	for (int y = 0; y < BRICKS_COUNT_VERTICAL; ++y) {
		for (int x = 0; x < BRICKS_COUNT_HORIZONTAL; ++x) {
			bricks_.push_back(Brick(x * BRICK_SIZE_X, (y + 3) * BRICK_SIZE_Y, colors[nextColor]));
			nextColor = nextColor < colorCount - 1 ? nextColor + 1 : 0;
		}
	}

	ball_.move(sf::Vector2f(0.7f, -0.7f));

	state_ = State::Running;
}

void Game::draw() {
	std::list<Brick>::iterator it;
	for (it = bricks_.begin(); it != bricks_.end(); ++it) {
		if (it->isDisabled()) continue;

		window_.draw(it->getShape());
	}

	window_.draw(pad_.getShape());
	window_.draw(ball_.getShape());
}

void Game::update(sf::Time deltaTime) {
	sf::Vector2i inputPosition = getMouseInput();
	//std::cout << "input:" << inputPosition.x << "," << inputPosition.y << std::endl;

	pad_.move(inputPosition.x);
	pad_.update(deltaTime);

	ball_.update(deltaTime);

	NormalDirections normal = NormalDirections::Up;

	if (testOutOfBounds(ball_, normal)) {
		ball_.bounce(normal);
	}

	std::list<Brick>::iterator it;
	for (it = bricks_.begin(); it != bricks_.end(); ++it) {
		if (it->isDisabled()) continue;

		if (ball_.testOverlap(*it, normal)) {
			ball_.bounce(normal);
			it->disable();
		}
	}

	if (ball_.testOverlap(pad_, normal)) {
		ball_.bounce(normal);
	}
}

sf::Vector2i Game::getMouseInput() {
	return sf::Mouse::getPosition(window_);
}

bool Game::testOutOfBounds(BoundingBox& boundingBox, NormalDirections& normal) {
	bool isOutOfBounds = false;
	sf::Vector2f position = boundingBox.getPosition();
	sf::Vector2i size = boundingBox.getSize();
	sf::Vector2f center = boundingBox.getCenter();

	if (position.x < 0) {
		isOutOfBounds = true;
		normal = NormalDirections::Right;
	}
	else if (position.x + size.x > BOARD_SIZE_X - 1) {
		isOutOfBounds = true;
		normal = NormalDirections::Left;
	}
	else if (position.y < 0) {
		isOutOfBounds = true;
		normal = NormalDirections::Down;
	}
	else if (position.y + size.y > BOARD_SIZE_Y - 1) {
		isOutOfBounds = true;
		normal = NormalDirections::Up;
	}

	return isOutOfBounds;
}