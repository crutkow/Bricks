#pragma once
#include <memory>

#include "brick.hpp"
#include "object_pool.hpp"

class Controller {
public:

public:
    static Controller& instance();

    void fillBrickPool(int fillCount);

protected:
    Controller() {};
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    ~Controller() {};

    ObjectPool<Brick> brickPool_;
};