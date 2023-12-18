#include "controller.hpp"

Controller& Controller::instance()
{
    static Controller inst;
    return inst;
}

void Controller::fillBrickPool(int fillCount) {
    for (int i = 0; i < fillCount; ++i) brickPool_.put(std::unique_ptr<Brick>(new Brick()));
}