#pragma once

#include <SFML/Graphics.hpp>

#include "config.hpp"

class Screen {
public:
	enum class Actions : uint {
		None,
		Win,
		Loose,
		Play,
		Quit,
	};

	enum class States : uint {
		Starting,
		Running,
		Ending,
	};

	~Screen() {}

	virtual void start() = 0;

	virtual void end() = 0;

	virtual void draw() = 0;

	virtual void update(sf::Time deltaTime) = 0;

	Actions getAction() const {
		return action_;
	}

	States getState() const {
		return state_;
	}

protected:
	Screen(sf::RenderWindow& window) : window_(window), action_(Actions::None), state_(States::Starting) { }

	sf::RenderWindow& window_;
	Actions action_;
	States state_;
};