#pragma once

#include "brick.hpp"

class Game {
public:
	enum class Action : uint {
		Start,
		Run,
		End,
	};

	enum class State : uint {
		Starting,
		Running,
		Ending,
	};

	void start();

	void step(float deltaTime);

private:
	State state_;
};