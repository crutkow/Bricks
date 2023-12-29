#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "screen.hpp"
#include "config.hpp"

class Menu : public Screen {
public:
	enum class MenuOptions : uint {
		Play,
		Quit,
	};

	Menu(sf::RenderWindow& window) : Screen(window), playTextFrame_(sf::Vector2f(MENU_TEXT_FRAME_SIZE_X, MENU_TEXT_FRAME_SIZE_Y)),
		quitTextFrame_(sf::Vector2f(MENU_TEXT_FRAME_SIZE_X, MENU_TEXT_FRAME_SIZE_Y)), menuOptionSelected_(MenuOptions::Play) { }

	void start(int arg) override;

	void end() override;

	void draw() override;

	void update(sf::Time deltaTime) override;

private:
	void makeTexts();

	sf::Font font_;
	sf::Text titleText_;
	sf::Text playText_;
	sf::Text quitText_;
	sf::RectangleShape playTextFrame_;
	sf::RectangleShape quitTextFrame_;
	MenuOptions menuOptionSelected_;
};