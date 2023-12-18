#pragma once
#include <memory>

typedef unsigned int uint;

class Brick {
public:
	Brick() : x_(0), y_(0) {

	}

	Brick(uint x, uint y) : x_(x), y_(y) {

	}


private:
	uint x_;
	uint y_;
};