#pragma once

enum State { LEFT, RIGHT, UP, DOWN, STAND };

#define ARROW_UP 72
#define	ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

const int CONSOLE_HEIGHT = 30;
const int CONSOLE_WIDTH = 120;
const int BOARD_WIDTH[3] = { 8, 16, 25 };
const int BOARD_HEIGHT[3] = { 8, 16, 25 };
const int NUMBER_MINES[3] = { 10, 40, 99 };


/*
8 * 8 10 mines
16 * 16 40 mines
25 * 25 99 mines
*/