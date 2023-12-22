#include "menu.hpp"

void Menu::start() {
	state_ = State::Running;
}


void Menu::end() {
	state_ = State::Starting;
}

void Menu::draw() {

}

void Menu::update(sf::Time deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		state_ = State::Ending;
	}
}