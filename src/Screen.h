#pragma once
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdbool.h>
#include "Utils.h"


// Function Prototypes  
//Nokia Screen
void SSI0_Init(void);
void ScreenInit(void);
void ScreenWrite(uint8_t type, uint8_t message);
void ScreenClear(void);
//Integration with nokia screen
void DrawScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void InitializeScreenGrid(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void UpdateScreenGridSnake(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point oldSnakeTail, const Point newSnakeHead);
void UpdateScreenGridApple(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point Apple);
uint8_t ExtractBlock(int x, int pageIndex, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void CreateStartScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void CreateGameOverScreen(int gameScore, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);

//Game Grid will not be used
void InitializeGameGrid(Block gameGrid[GAME_GRID_X][GAME_GRID_Y]);
void GameGridToScreenGrid(const Block inputGameGrid[GAME_GRID_X][GAME_GRID_Y], bool outputScreenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
