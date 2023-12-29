#include "menu.hpp"

void Menu::makeTexts() {
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
	playTextFrame_.setPosition(sf::Vector2f(MENU_PLAY_TEXT_FRAME_POSITION_X, MENU_PLAY_TEXT_FRAME_POSITION_Y));
	playTextFrame_.setFillColor(sf::Color::Yellow);

	quitText_.setFont(font_);
	quitText_.setString("QUIT");
	quitText_.setCharacterSize(MENU_QUIT_TEXT_SIZE);
	quitText_.setFillColor(sf::Color::Blue);
	quitText_.setPosition(MENU_QUIT_TEXT_POSITION_X, MENU_QUIT_TEXT_POSITION_Y);
	quitTextFrame_.setPosition(sf::Vector2f(MENU_QUIT_TEXT_FRAME_POSITION_X, MENU_QUIT_TEXT_FRAME_POSITION_Y));
	quitTextFrame_.setFillColor(sf::Color::Yellow);
}

void Menu::start(int arg) {
	makeTexts();
	state_ = States::Running;
}


void Menu::end() {
	state_ = States::Starting;
}

void Menu::draw() {
	window_.draw(titleText_);
	switch (menuOptionSelected_)
	{
	case Menu::MenuOptions::Play:
		window_.draw(playTextFrame_);
		break;
	case Menu::MenuOptions::Quit:
		window_.draw(quitTextFrame_);
		break;
	}
	window_.draw(playText_);
	window_.draw(quitText_);
}

void Menu::update(sf::Time deltaTime) {
	sf::Vector2i inputPosition = sf::Mouse::getPosition(window_);

	if (inputPosition.x >= MENU_PLAY_TEXT_FRAME_POSITION_X && inputPosition.x < MENU_PLAY_TEXT_FRAME_POSITION_X + MENU_TEXT_FRAME_SIZE_X &&
		inputPosition.y >= MENU_PLAY_TEXT_FRAME_POSITION_Y && inputPosition.y < MENU_PLAY_TEXT_FRAME_POSITION_Y + MENU_TEXT_FRAME_SIZE_Y)
	{
		menuOptionSelected_ = Menu::MenuOptions::Play;
	}
	else if (inputPosition.x >= MENU_QUIT_TEXT_FRAME_POSITION_X && inputPosition.x < MENU_QUIT_TEXT_FRAME_POSITION_X + MENU_TEXT_FRAME_SIZE_X &&
		     inputPosition.y >= MENU_QUIT_TEXT_FRAME_POSITION_Y && inputPosition.y < MENU_QUIT_TEXT_FRAME_POSITION_Y + MENU_TEXT_FRAME_SIZE_Y)
	{
		menuOptionSelected_ = Menu::MenuOptions::Quit;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		switch (menuOptionSelected_)
		{
		case Menu::MenuOptions::Play:
			action_ = Actions::Play;
			break;
		case Menu::MenuOptions::Quit:
			action_ = Actions::Quit;
			break;
		}
		state_ = States::Ending;
	}
}