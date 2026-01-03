#pragma once
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdbool.h>
#include "Utils.h"

// Nokia Screen
void SSI0_Init(void);
void ScreenInit(void);
void ScreenWrite(uint8_t type, uint8_t message);
void ScreenClear(void);
// Integration with nokia screen
void DrawScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void InitializeScreenGrid(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], Point* snake, int snakeLength);
void UpdateScreenGridSnake(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point oldSnakeTail, const Point newSnakeHead, const Point *snake);
void UpdateScreenGridApple(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point Apple);
uint8_t ExtractBlock(int x, int pageIndex, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void CreateStartScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void CreateGameOverScreen(int gameScore, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
