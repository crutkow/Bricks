#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <streambuf>

#include "game.hpp"

void Game::start() {
	bricks_.clear();

	std::string levelString = readLevel("levels/level1.lvl");

	int x = 0;
	int y = 0;
	sf::Color color = sf::Color::Red;
	bool indestructible = false;
	for (char& c : levelString) {
		if (c == '\n') {
			y++;
			x = 0;
			continue;
		}
		else if (c == '0') {
			x++;
			continue;
		}
		else if (c == '1') {
			color = sf::Color::Yellow;
			indestructible = true;
		}
		else if (c == '2') {
			color = sf::Color::Red;
			indestructible = false;
		}
		else if (c == '3') {
			color = sf::Color::Magenta;
			indestructible = false;
		}

		bricks_.push_back(Brick(BOARD_BOUND_SIZE_X + x * BRICK_SIZE_X, BOARD_BOUND_SIZE_Y + y * BRICK_SIZE_Y, color, indestructible));
		x++;
	}

	isGameLost_ = false;
	isGameWon_ = false;

	pad_ = Pad(PAD_START_POSITION_X, PAD_START_POSITION_Y);
	ball_ = Ball(BALL_START_POSITION_X, BALL_START_POSITION_Y);

	state_ = States::Running;
}

void Game::end() {
	state_ = States::Starting;
}

void Game::draw() {
	window_.draw(leftBound_);
	window_.draw(rightBound_);
	window_.draw(topBound_);

	std::list<Brick>::iterator it;
	for (it = bricks_.begin(); it != bricks_.end(); ++it) {
		if (it->isDisabled()) continue;

		window_.draw(it->getShape());
	}

	window_.draw(pad_.getShape());
	window_.draw(ball_.getShape());

	if (isGameWon_) {
		window_.draw(winText_);
	}
	else if (isGameLost_) {
		window_.draw(loseText_);
	}
}

void Game::update(sf::Time deltaTime) {
	NormalDirections normal = NormalDirections::Up;

	// Input
	sf::Vector2i inputPosition = sf::Mouse::getPosition(window_);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (isGameLost_ || isGameWon_) {
			state_ = States::Ending;
		}
		else if (ball_.isMovingHorizontaly()) {
			ball_.move(sf::Vector2f((float)cos(M_PI_2 / 2), -(float)sin(M_PI_2 / 2)));
		}
	}

	if (isGameLost_ || isGameWon_) {
		return;
	}

	// Pad moving
	pad_.move(inputPosition.x);
	pad_.update(deltaTime);

	// Ball moving horizontally sticked to pad
	if (ball_.isMovingHorizontaly()) {
		ball_.moveHorizontaly(pad_.getCenter().x);
	}

	// Ball update
	ball_.update(deltaTime);

	// Ball bouncing of walls
	if (testOutOfBounds(ball_, normal)) {
		if (normal == NormalDirections::Up) {
			isGameLost_ = true;
		}
		else {
			ball_.bounce(normal);
		}
	}

	// Ball bouncing of bricks
	std::list<Brick>::iterator it;
	for (it = bricks_.begin(); it != bricks_.end(); ++it) {
		if (it->isDisabled()) continue;

		if (ball_.testOverlap(*it, normal)) {
			ball_.bounce(normal);
			if (!it->isIndestructible()) {
				it->setActive(false);
			}
		}
	}

	// Test success, all bricks hit by ball
	bool isAnyBrickActive = false;
	for (it = bricks_.begin(); it != bricks_.end(); ++it) {
		if (!it->isDisabled() && !it->isIndestructible()) isAnyBrickActive = true;
	}
	if (!isAnyBrickActive) {
		isGameWon_ = true;
	}

	// Ball bouncing of pad
	if (!ball_.isMovingHorizontaly() && ball_.testOverlap(pad_, normal)) {
		float factor = abs(ball_.getCenter().x - pad_.getCenter().x) / (PAD_SIZE_X / 2);
		int sign = ball_.getCenter().x - pad_.getCenter().x < 0 ? -1 : 1;
		sf::Vector2f moveVector((float)cos(M_PI_2 * (1 - factor)) * sign, -(float)sin(M_PI_2 * (1 - factor)));
		ball_.move(moveVector);
	}
}

bool Game::testOutOfBounds(BoundingBox const& boundingBox, NormalDirections& normal) {
	bool isOutOfBounds = false;
	sf::Vector2f position = boundingBox.getPosition();
	sf::Vector2i size = boundingBox.getSize();
	sf::Vector2f center = boundingBox.getCenter();

	if (position.x < BOARD_BOUND_SIZE_X) {
		isOutOfBounds = true;
		normal = NormalDirections::Right;
	}
	else if (position.x + size.x > BOARD_SIZE_X - BOARD_BOUND_SIZE_X - 1) {
		isOutOfBounds = true;
		normal = NormalDirections::Left;
	}
	else if (position.y < BOARD_BOUND_SIZE_Y) {
		isOutOfBounds = true;
		normal = NormalDirections::Down;
	}
	else if (position.y + size.y > BOARD_SIZE_Y - BOARD_BOUND_SIZE_Y - 1) {
		isOutOfBounds = true;
		normal = NormalDirections::Up;
	}

	return isOutOfBounds;
}

void Game::makeBounds() {
	leftBound_.setFillColor(sf::Color::Blue);
	leftBound_.setPosition(0, BOARD_BOUND_SIZE_Y);

	rightBound_.setFillColor(sf::Color::Blue);
	rightBound_.setPosition(BOARD_SIZE_X - BOARD_BOUND_SIZE_X, BOARD_BOUND_SIZE_Y);

	topBound_.setFillColor(sf::Color::Blue);
}

void Game::makeTexts() {
	if (!font_.loadFromFile("Roboto-Black.ttf"))
	{
		// error...
	}

	winText_.setFont(font_);
	winText_.setString("SUCCESS");
	winText_.setCharacterSize(GAME_TEXT_SIZE);
	winText_.setFillColor(sf::Color::Red);
	winText_.setPosition(GAME_TEXT_POSITION_X, GAME_TEXT_POSITION_Y);

	loseText_.setFont(font_);
	loseText_.setString("GAME OVER");
	loseText_.setCharacterSize(GAME_TEXT_SIZE);
	loseText_.setFillColor(sf::Color::Red);
	loseText_.setPosition(GAME_TEXT_POSITION_X, GAME_TEXT_POSITION_Y);
}

std::string Game::readLevel(const std::string path) {
	std::ifstream levelFile;

	try {
		levelFile.open(path);
	}
	catch (const std::ifstream::failure e) {
		std::cout << "File not found: " << path << std::endl;
	}

	std::string str((std::istreambuf_iterator<char>(levelFile)),
		             std::istreambuf_iterator<char>());

	return str;
}