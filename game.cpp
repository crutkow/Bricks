#include "game.hpp"

void Game::start() {
	sf::Color colors[] = { sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green };
	const int colorCount = 4;
	int nextColor = 0;

	bricks_.clear();

	for (int y = 0; y < BRICKS_COUNT_VERTICAL; ++y) {
		for (int x = 0; x < BRICKS_COUNT_HORIZONTAL; ++x) {
			bricks_.push_back(Brick(x * BRICK_SIZE_X, y * BRICK_SIZE_Y, colors[nextColor]));
			nextColor = nextColor < colorCount - 1 ? nextColor + 1 : 0;
		}
	}

	state_ = State::Running;
}

void Game::draw() {
	std::list<Brick>::iterator it;
	for (it = bricks_.begin(); it != bricks_.end(); ++it) {
		window_.draw(it->getShape());
	}

	window_.draw(pad_.getShape());
}

void Game::update(sf::Time deltaTime) {

}