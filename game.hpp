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
		pad_(PAD_START_POSITION_X, PAD_START_POSITION_Y), 
		ball_(BALL_START_POSITION_X, BALL_START_POSITION_Y) {
	}

	void start() override;

	void end() override;

	void draw() override;

	void update(sf::Time deltaTime) override;

private:
	bool testOutOfBounds(BoundingBox& boundingBox, NormalDirections& normal);

	std::list<Brick> bricks_;
	Pad pad_;
	Ball ball_;
};