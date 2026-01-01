#pragma once
#ifndef _MYHEADER_UTILS_
#define _MYHEADER_UTILS_
#include <stdint.h>
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
    unsigned char x; // 0 to 20
    unsigned char y; // 0 to 11
} Point;

#endif