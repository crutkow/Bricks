#pragma once

typedef unsigned int uint;

constexpr unsigned FRAME_RATE = 60;
constexpr unsigned BRICK_POOL_SIZE = 100;
constexpr unsigned BRICK_SIZE_X = 40;
constexpr unsigned BRICK_SIZE_Y = 20;
constexpr unsigned BOARD_SIZE_X = 400;
constexpr unsigned BOARD_SIZE_Y = 400;
constexpr unsigned BRICKS_COUNT_HORIZONTAL = 10;
constexpr unsigned BRICKS_COUNT_VERTICAL = 5;
constexpr unsigned PAD_SIZE_X = 60;
constexpr unsigned PAD_SIZE_Y = 20;
constexpr unsigned PAD_START_POSITION_X = BOARD_SIZE_X / 2 - PAD_SIZE_X / 2;
constexpr unsigned PAD_START_POSITION_Y = BOARD_SIZE_Y - PAD_SIZE_Y;
constexpr float    PAD_MOVE_SPEED = 3.0f;
constexpr unsigned BALL_RADIUS = 10;
constexpr unsigned BALL_START_POSITION_X = BOARD_SIZE_X / 2 - PAD_SIZE_X / 2;
constexpr unsigned BALL_START_POSITION_Y = BOARD_SIZE_Y - PAD_SIZE_Y - BALL_RADIUS * 2;
constexpr float    BALL_MOVE_SPEED = 4.0f;