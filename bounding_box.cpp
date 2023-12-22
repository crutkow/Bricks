#include "bounding_box.hpp"

bool BoundingBox::testOverlap(BoundingBox const & boundingBox, NormalDirections& normal) const {
	sf::Vector2f firstPosition = getPosition();
	sf::Vector2i firstSize = getSize();
	sf::Vector2f firstCenter = getCenter();
	sf::Vector2f secondPosition = boundingBox.getPosition();
	sf::Vector2i secondSize = boundingBox.getSize();

	sf::Vector2f firstUpLeftCorner(firstPosition.x, firstPosition.y);
	sf::Vector2f firstUpRightCorner(firstPosition.x + firstSize.x, firstPosition.y);
	sf::Vector2f firstDownLeftCorner(firstPosition.x, firstPosition.y + firstSize.y);
	sf::Vector2f firstDownRightCorner(firstPosition.x + firstSize.x, firstPosition.y + firstSize.y);

	// Check if any corner is contained
	if (!(checkPointIsContained(firstUpLeftCorner, boundingBox) || checkPointIsContained(firstUpRightCorner, boundingBox) ||
		checkPointIsContained(firstDownLeftCorner, boundingBox) || checkPointIsContained(firstDownRightCorner, boundingBox))) {
		return false;
	}

	// Naive overlap normal set
	if (firstCenter.y < secondPosition.y) {
		normal = NormalDirections::Up;
	}
	else if (firstCenter.y > secondPosition.y + secondSize.y) {
		normal = NormalDirections::Down;
	}
	else if (firstCenter.x < secondPosition.x) {
		normal = NormalDirections::Left;
	}
	else {
		normal = NormalDirections::Right;
	}

	return true;
}

bool BoundingBox::checkPointIsContained(sf::Vector2f point, BoundingBox const & boundingBox) const {
	auto boxPosition = boundingBox.getPosition();
	auto boxSize = boundingBox.getSize();
	if (point.x >= boxPosition.x && point.x < boxPosition.x + boxSize.x &&
		point.y >= boxPosition.y && point.y < boxPosition.y + boxSize.y) {
		return true;
	}

	return false;
}