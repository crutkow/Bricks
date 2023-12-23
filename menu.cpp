#include "menu.hpp"

void Menu::start() {
	if (!font_.loadFromFile("Roboto-Black.ttf"))
	{
		// error...
	}

	titleText_.setFont(font_);
	titleText_.setString("BRICKS");
	titleText_.setCharacterSize(MENU_TITLE_TEXT_SIZE);
	titleText_.setFillColor(sf::Color::Red);
	titleText_.setPosition(MENU_TITLE_TEXT_POSITION_X, MENU_TITLE_TEXT_POSITION_Y);

	playText_.setFont(font_);
	playText_.setString("PLAY");
	playText_.setCharacterSize(MENU_PLAY_TEXT_SIZE);
	playText_.setFillColor(sf::Color::Blue);
	playText_.setPosition(MENU_PLAY_TEXT_POSITION_X, MENU_PLAY_TEXT_POSITION_Y);

	quitText_.setFont(font_);
	quitText_.setString("QUIT");
	quitText_.setCharacterSize(MENU_QUIT_TEXT_SIZE);
	quitText_.setFillColor(sf::Color::Blue);
	quitText_.setPosition(MENU_QUIT_TEXT_POSITION_X, MENU_QUIT_TEXT_POSITION_Y);

	state_ = State::Running;
}


void Menu::end() {
	state_ = State::Starting;
}

void Menu::draw() {
	window_.draw(titleText_);
	window_.draw(playText_);
	window_.draw(quitText_);
}

void Menu::update(sf::Time deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		state_ = State::Ending;
	}
}