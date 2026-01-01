#pragma once
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdbool.h>
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
	unsigned char x; //0 to 20
	unsigned char y; //0 to 11
} Point;

// Function Prototypes  
//Nokia Screen
void SSI0_Init(void);
void ScreenInit(void);
void ScreenWrite(uint8_t type, uint8_t message);
void ScreenClear(void);
//Integration with nokia screen
void ScreenWriteGrid(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void InitializeScreenGrid(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
void UpdateScreenGridSnake(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point* Snake, const int snakeLength);
void UpdateScreenGridApple(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point Apple);
uint8_t ExtractBlock(int x, int pageIndex, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);

//Game Grid will not be used
void InitializeGameGrid(Block gameGrid[GAME_GRID_X][GAME_GRID_Y]);
void GameGridToScreenGrid(const Block inputGameGrid[GAME_GRID_X][GAME_GRID_Y], bool outputScreenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);


//Utils
void Delay(uint32_t n);
