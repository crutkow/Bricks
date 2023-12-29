#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <ostream>
#include <streambuf>
#include <time.h>

#include "game.hpp"

void Game::start(int arg) {
	srand((unsigned)time(NULL));

	startLevel(arg);

	action_ = Actions::None;
	state_ = States::Running;
}

void Game::end() {
	state_ = States::Starting;
}

void Game::draw() {
	window_.draw(leftBound_);
	window_.draw(rightBound_);
	window_.draw(topBound_);

	for (auto& brick : bricks_) {
		if (brick.isDisabled()) continue;

		window_.draw(brick.getShape());
	}

	for (auto ball : balls_) {
		window_.draw(ball->getShape());
	}

	window_.draw(pad_.getShape());

	for (auto& drop : drops_) {
		if (drop.isDisabled()) continue;

		window_.draw(drop.getShape());
		for (int i = 0; i < DROP_CIRCLE_COUNT; ++i) {
			window_.draw(drop.getCircleShape(i));
		}
	}

	if (action_ == Actions::Win) {
		window_.draw(winText_);
	}
	else if (action_ == Actions::Loose) {
		window_.draw(loseText_);
	}
}

void Game::update(sf::Time deltaTime) {
	NormalDirections normal = NormalDirections::Up;

	// Input
	sf::Vector2i inputPosition = sf::Mouse::getPosition(window_);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (action_ == Actions::Win || action_ == Actions::Loose) {
			state_ = States::Ending;
		}
		else if (firstBall_->isMovingHorizontaly()) {
			firstBall_->move(sf::Vector2f(0, -1));
		}
	}

	if (action_ == Actions::Win || action_ == Actions::Loose) {
		return;
	}

	// Pad moving
	pad_.move(inputPosition.x);
	pad_.update(deltaTime);

	// Drops update
	for (auto& drop : drops_) {
		if (drop.isDisabled()) continue;

		drop.update(deltaTime);

		if (drop.testOverlap(pad_, normal)) {
			drop.setActive(false);

			std::vector<std::shared_ptr<Ball> > newBalls;
			for (auto ball : balls_) {
				auto newBall = std::shared_ptr<Ball>(new Ball((uint)ball->getCenter().x, (uint)ball->getCenter().y));
				newBall->move(sf::Vector2f((float)cos(M_PI_4), -(float)sin(M_PI_4)));
				newBalls.push_back(newBall);
				newBall = std::shared_ptr<Ball>(new Ball((uint)ball->getCenter().x, (uint)ball->getCenter().y));
				newBall->move(sf::Vector2f(-(float)cos(M_PI_4), -(float)sin(M_PI_4)));
				newBalls.push_back(newBall);
			}
			balls_.insert(balls_.end(), newBalls.begin(), newBalls.end());
		}
	}

	// First ball moving horizontally sticked to pad
	if (firstBall_->isMovingHorizontaly()) {
		firstBall_->moveHorizontaly(pad_.getCenter().x);
	}

	// Balls update
	std::vector<std::shared_ptr<Ball> > removeBalls;
	for (auto ball : balls_) {
		ball->update(deltaTime);

		if (testOutOfBounds(*ball, normal)) {
			if (normal == NormalDirections::Up) {
				removeBalls.push_back(ball);
			}
			else {
				ball->bounce(normal);
			}
		}
	}
	for (auto removeBall : removeBalls) {
		balls_.remove(removeBall);
	}

	if (balls_.empty()) {
		action_ = Actions::Loose;
	}

	// Bricks update
	bool anyBrickActive = false;
	for (auto& brick : bricks_) {
		if (!brick.isDisabled() && !brick.isIndestructible()) anyBrickActive = true;

		if (brick.isDisabled()) continue;

		for (auto ball : balls_) {
			if (ball->testOverlap(brick, normal)) {
				ball->bounce(normal);
				if (!brick.isIndestructible()) {
					brick.setActive(false);
					spawnDropChance((uint)brick.getPosition().x, (uint)brick.getPosition().y);
				}
			}
		}
	}

	if (!anyBrickActive) {
		action_ = Actions::Win;
	}

	// Balls bouncing of pad
	for (auto ball : balls_) {
		if (!ball->isMovingHorizontaly() && ball->testOverlap(pad_, normal)) {
			float factor = abs(ball->getCenter().x - pad_.getCenter().x) / (PAD_SIZE_X / 2);
			int sign = ball->getCenter().x - pad_.getCenter().x < 0 ? -1 : 1;
			sf::Vector2f moveVector((float)cos(M_PI_2 * (1 - factor)) * sign, -(float)sin(M_PI_2 * (1 - factor)));
			ball->move(moveVector);
		}
	}
}

void Game::startLevel(int level) {
	char buff[256];
	snprintf(buff, sizeof(buff), "levels/level%d.lvl", level);
	std::string levelPath = buff;
	std::string levelString = readLevel(levelPath);

	bricks_.clear();

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

	drops_.clear();

	balls_.clear();
	firstBall_ = std::shared_ptr<Ball>(new Ball(BALL_START_POSITION_X, BALL_START_POSITION_Y));
	balls_.push_back(firstBall_);

	pad_ = Pad(PAD_START_POSITION_X, PAD_START_POSITION_Y);
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
	else if (position.y + size.y > BOARD_SIZE_Y - 1) {
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

void Game::spawnDropChance(uint x, uint y) {
	float random = (rand() % 100) / 100.0f;

	if (random <= DROP_SPAWN_RATE) {
		drops_.push_back(Drop(x, y));
	}
}