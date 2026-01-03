#pragma once
#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdbool.h>
#include "Utils.h"

// Nokia Screen
//Initializzes the SSI0 for communication with the screen
void SSI0_Init(void);
//Initializes the nokia screen
void ScreenInit(void);
//Writes to nokia screen
void ScreenWrite(uint8_t type, uint8_t message);
//Clears the nokia screen
void ScreenClear(void);
// Integration with nokia screen
//Draw the grid on the nokia screen
void DrawScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
//Initilize the screen grid for start of the game
void InitializeScreenGrid(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], Point* snake, int snakeLength);
//Update the screen grid after snake moves
void UpdateScreenGridSnake(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point oldSnakeTail, const Point newSnakeHead, const Point *snake);
//Update the screen grid after the apple is resetted
void UpdateScreenGridApple(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point Apple);
//Turn the screen grid to 8 bit blocks as nokia screen wants
uint8_t ExtractBlock(int x, int pageIndex, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
//Create the start screen in the screen grid, "Snake" "Press button to start game" is writen
void CreateStartScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
//Create the game over screen in the screen grid, "Game Over" and the score is written
void CreateGameOverScreen(int gameScore, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]);
