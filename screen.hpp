#pragma once

#include <SFML/Graphics.hpp>

#include "config.hpp"

class Screen {
public:
	enum class State : uint {
		Starting,
		Running,
		Ending,
	};

	~Screen() {}

	virtual void start() = 0;

	virtual void end() = 0;

	virtual void draw() = 0;

	virtual void update(sf::Time deltaTime) = 0;

	State getState() const {
		return state_;
	}

protected:
	Screen(sf::RenderWindow& window) : window_(window), state_(State::Starting) { }

	sf::RenderWindow& window_;
	State state_;
};