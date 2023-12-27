#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "config.hpp"
#include "screen.hpp"
#include "brick.hpp"
#include "pad.hpp"
#include "ball.hpp"

class Game : public Screen {
public:
	Game(sf::RenderWindow& window) : Screen(window),
		leftBound_(sf::Vector2f(BOARD_BOUND_SIZE_X, BOARD_SIZE_Y - BOARD_BOUND_SIZE_Y)),
		rightBound_(sf::Vector2f(BOARD_BOUND_SIZE_X, BOARD_SIZE_Y - BOARD_BOUND_SIZE_Y)),
		topBound_(sf::Vector2f(BOARD_SIZE_X, BOARD_BOUND_SIZE_Y)),
		pad_(PAD_START_POSITION_X, PAD_START_POSITION_Y), 
		ball_(BALL_START_POSITION_X, BALL_START_POSITION_Y),
		isGameWon_(false), isGameLost_(false) {
		makeBounds();
		makeTexts();
	}

	void start() override;

	void end() override;

	void draw() override;

	void update(sf::Time deltaTime) override;

private:
	bool testOutOfBounds(BoundingBox const& boundingBox, NormalDirections& normal);
	void makeBounds();
	void makeTexts();
	std::string readLevel(const std::string path);

	sf::RectangleShape leftBound_;
	sf::RectangleShape rightBound_;
	sf::RectangleShape topBound_;
	std::list<Brick> bricks_;
	Pad pad_;
	Ball ball_;
	sf::Font font_;
	sf::Text winText_;
	sf::Text loseText_;
	bool isGameWon_;
	bool isGameLost_;
};