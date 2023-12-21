#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "config.hpp"

enum class NormalDirections {
	Up,
	Down,
	Left,
	Right,
};

class BoundingBox {
public:
	virtual sf::Vector2f getPosition() = 0;
	virtual sf::Vector2i getSize() = 0;
	virtual sf::Vector2f getCenter() = 0;

	bool testOverlap(BoundingBox& boundingBox, NormalDirections &normal);
protected:
	bool checkPointIsContained(sf::Vector2f point, BoundingBox& boundingBox);
};