#pragma once

typedef unsigned int uint;

constexpr unsigned FRAME_RATE = 60;
constexpr unsigned BOARD_SIZE_X = 1000;
constexpr unsigned BOARD_SIZE_Y = 1000;
constexpr unsigned BOARD_BOUND_SIZE_X = 100;
constexpr unsigned BOARD_BOUND_SIZE_Y = 100;
constexpr unsigned BRICKS_COUNT_HORIZONTAL = 20;
constexpr unsigned BRICKS_COUNT_VERTICAL = 5;
constexpr unsigned BRICK_SIZE_X = 40;
constexpr unsigned BRICK_SIZE_Y = 20;
constexpr float    BRICK_OUTLINE_SIZE = 2.5f;
constexpr unsigned PAD_SIZE_X = 160;
constexpr unsigned PAD_SIZE_Y = 40;
constexpr unsigned PAD_START_POSITION_X = BOARD_SIZE_X / 2 - PAD_SIZE_X / 2;
constexpr unsigned PAD_START_POSITION_Y = BOARD_SIZE_Y - PAD_SIZE_Y - BOARD_BOUND_SIZE_Y;
constexpr float    PAD_MOVE_SPEED = 5.0f;
constexpr unsigned BALL_RADIUS = 10;
constexpr unsigned BALL_START_POSITION_X = BOARD_SIZE_X / 2 - PAD_SIZE_X / 2;
constexpr unsigned BALL_START_POSITION_Y = PAD_START_POSITION_Y - BALL_RADIUS * 2;
constexpr float    BALL_MOVE_SPEED = 6.0f;
constexpr unsigned MENU_TITLE_TEXT_SIZE = 50;
constexpr unsigned MENU_TITLE_TEXT_POSITION_X = 120;
constexpr unsigned MENU_TITLE_TEXT_POSITION_Y = 50;
constexpr unsigned MENU_PLAY_TEXT_SIZE = 40;
constexpr unsigned MENU_PLAY_TEXT_POSITION_X = 150;
constexpr unsigned MENU_PLAY_TEXT_POSITION_Y = 200;
constexpr unsigned MENU_QUIT_TEXT_SIZE = 40;
constexpr unsigned MENU_QUIT_TEXT_POSITION_X = 150;
constexpr unsigned MENU_QUIT_TEXT_POSITION_Y = 250;
constexpr unsigned MENU_TEXT_FRAME_SIZE_X = 200;
constexpr unsigned MENU_TEXT_FRAME_SIZE_Y = 50;
constexpr unsigned MENU_PLAY_TEXT_FRAME_POSITION_X = 100;
constexpr unsigned MENU_PLAY_TEXT_FRAME_POSITION_Y = 200;
constexpr unsigned MENU_QUIT_TEXT_FRAME_POSITION_X = 100;
constexpr unsigned MENU_QUIT_TEXT_FRAME_POSITION_Y = 250;
constexpr unsigned GAME_TEXT_SIZE = 40;
constexpr unsigned GAME_TEXT_POSITION_X = 100;
constexpr unsigned GAME_TEXT_POSITION_Y = 180;