#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <list>

#include "config.hpp"
#include "screen.hpp"
#include "brick.hpp"
#include "pad.hpp"
#include "ball.hpp"
#include "drop.hpp"

class Game : public Screen {
public:
	Game(sf::RenderWindow& window) : Screen(window),
		leftBound_(sf::Vector2f(BOARD_BOUND_SIZE_X, BOARD_SIZE_Y - BOARD_BOUND_SIZE_Y)),
		rightBound_(sf::Vector2f(BOARD_BOUND_SIZE_X, BOARD_SIZE_Y - BOARD_BOUND_SIZE_Y)),
		topBound_(sf::Vector2f(BOARD_SIZE_X, BOARD_BOUND_SIZE_Y)),
		textFrame_(sf::Vector2f(GAME_TEXT_FRAME_SIZE_X, GAME_TEXT_FRAME_SIZE_Y)),
		pad_(PAD_START_POSITION_X, PAD_START_POSITION_Y) {
		makeBounds();
		makeTexts();
	}

	void start(int arg) override;

	void end() override;

	void draw() override;

	void update(sf::Time deltaTime) override;

private:
	void startLevel(int level);
	std::string readLevel(const std::string path);
	bool testOutOfBounds(BoundingBox const& boundingBox, NormalDirections& normal);
	void makeBounds();
	void makeTexts();
	void spawnDropChance(uint x, uint y);

	sf::RectangleShape leftBound_;
	sf::RectangleShape rightBound_;
	sf::RectangleShape topBound_;
	sf::Font font_;
	sf::Text winText_;
	sf::Text loseText_;
	sf::RectangleShape textFrame_;
	Pad pad_;
	std::vector<Brick> bricks_;
	std::list<std::shared_ptr<Ball> > balls_;
	std::shared_ptr<Ball> firstBall_;
	std::vector<Drop> drops_;
};