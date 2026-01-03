#pragma once
#ifndef _MYHEADER_UTILS_
#define _MYHEADER_UTILS_
#include <stdint.h>
//Constants
#define GAME_GRID_X 20
#define GAME_GRID_Y 11
#define SCREEN_WIDTH 84
#define SCREEN_HEIGHT 48

typedef enum
{
    BLANK, // 0
    SNAKE, // 1
    APPLE  // 2
} Block;

typedef struct
{
    int x; // 0 to 20
    int y; // 0 to 11
} Point;

typedef enum
{
    UP_DIR, // 0
    RIGHT_DIR, // 1
    DOWN_DIR, // 2
    LEFT_DIR  // 3
} Direction;

typedef struct
{
    int pitch; // 0 to 20
    int duration; // 0 to 11
} SoundNote;

#endif