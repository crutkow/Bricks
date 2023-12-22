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
	virtual sf::Vector2f getPosition() const = 0;
	virtual sf::Vector2i getSize() const = 0;
	virtual sf::Vector2f getCenter() const = 0;

	bool testOverlap(BoundingBox const & boundingBox, NormalDirections &normal) const;
protected:
	bool checkPointIsContained(sf::Vector2f point, BoundingBox const & boundingBox) const;
};