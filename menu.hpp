#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "screen.hpp"
#include "config.hpp"

class Menu : public Screen {
public:
	Menu(sf::RenderWindow& window) : Screen(window) { }

	void start() override;

	void end() override;

	void draw() override;

	void update(sf::Time deltaTime) override;

private:
	sf::Font font_;;
	sf::Text titleText_;
	sf::Text playText_;
	sf::Text quitText_;
};