#pragma once

#include <memory>

#include "config.hpp"
#include "brick.hpp"
#include "object_pool.hpp"

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

	Game() : state_(State::Starting) {
		for (int i = 0; i < BRICK_POOL_SIZE; ++i) {
			brickPool_.put(std::unique_ptr<Brick>(new Brick()));
		}
	}

	void start();

	void step(float deltaTime);

private:
	State state_;
	ObjectPool<Brick> brickPool_;
};