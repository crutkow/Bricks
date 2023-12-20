#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "config.hpp"
#include "brick.hpp"
#include "pad.hpp"
#include "ball.hpp"

class Game {
public:
	enum class Action : uint {
		Start,
		Run,
		End,
	};

	enum class State : uint {
		Starting,
		Running,
		Ending,
	};

	Game(sf::RenderWindow& window) : window_(window), pad_(PAD_START_POSITION_X, PAD_START_POSITION_Y), 
		ball_(BALL_START_POSITION_X, BALL_START_POSITION_Y), state_(State::Starting) {
	}

	void start();

	void draw();

	void update(sf::Time deltaTime);

	sf::Vector2i getMouseInput();

private:
	sf::RenderWindow& window_;
	State state_;
	std::list<Brick> bricks_;
	Pad pad_;
	Ball ball_;
};