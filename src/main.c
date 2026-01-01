#include "Screen.h"

// Pixels in the screen
bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT];

//Snake
int snakeLength;
Point Snake[SCREEN_HEIGHT*SCREEN_WIDTH];
//Apple
Point Apple;

// ---------------------------------------------------------------------------
// MAIN (Test Loop)
// ---------------------------------------------------------------------------
int main(void)
{

  // Initialize
  ScreenInit();

  // Clear any random noise
  ScreenClear();

  // Reset Cursor to top left
  ScreenWrite(0, 0x80);
  ScreenWrite(0, 0x40);

  //Create Snake and Apple
  snakeLength = 3;
  Apple.x = 2;
  Apple.y = 3;
  Snake[0].x = 0;
  Snake[0].y = 0;
  Snake[1].x = 1;
  Snake[1].y = 0;
  Snake[2].x = 2;
  Snake[2].y = 0;
  InitializeScreenGrid(screenGrid);
  UpdateScreenGridSnake(screenGrid, Snake, snakeLength);
  UpdateScreenGridApple(screenGrid, Apple);
  ScreenWriteGrid(screenGrid);

  // Loop forever drawing a pattern
  while (1)
  {
  UpdateScreenGridSnake(screenGrid, Snake, snakeLength);
  UpdateScreenGridApple(screenGrid, Apple);
  ScreenWriteGrid(screenGrid);
  }
}