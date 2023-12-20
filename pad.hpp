#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"
#include "brick.hpp"

class Pad : public Brick {
public:
	Pad(uint x, uint y) : Brick(x, y, sf::Color::Blue, sf::Vector2f(PAD_SIZE_X, PAD_SIZE_Y)) {
	}
};