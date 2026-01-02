#include <string.h>
#include "Screen.h"
#include "Game_Logic.h"
#include "buzzer.h"
#include "button_read.h"

void Delay2(uint32_t n)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
  volatile uint32_t time;
#pragma GCC diagnostic pop
  while (n > 0)
  {
    time = n; // Dummy operation
    n--;
  }
}

// Global Variables

bool ScreenGrid[SCREEN_WIDTH][SCREEN_HEIGHT]; // Pixels in the screen
// Snake
int SnakeLength;
Point Snake[GAME_GRID_X * GAME_GRID_Y];
int SnakeDir;
Point Apple;
int ControllerDir;
bool isGameOver;

bool IsStartButtonPressed()
{
  return IsPF4PressedDebounced();
}

int ReadController()
{
 
	// Direction from the accelerator controller
  return 0;
}

void GameOver(int gameScore)
{
  CreateGameOverScreen(gameScore, ScreenGrid);
  //ScreenClear();

  while (IsStartButtonPressed())
  {
    // Delay
  }
  return;
}

void StartScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
  CreateStartScreen(screenGrid);
  DrawScreen(screenGrid);
  while (!IsStartButtonPressed())
  {
    // Delay
  }
  return;
}

int main(void)
{
  //Init start button
  InitPF4();
  // Buzzer init
  InitBuzzer();
  // Screen Initialize
  ScreenInit();
  ScreenClear();
  ScreenWrite(0, 0x80);
  ScreenWrite(0, 0x40);

  // Start screen
  StartScreen(ScreenGrid);

  // Game Initialization
  Apple.x = 10;
  Apple.y = 7;
  Snake[0].x = 10;
  Snake[0].y = 9;
  SnakeLength = 1;
  SnakeDir = 0;
  InitializeScreenGrid(ScreenGrid);
  UpdateScreenGridSnake(ScreenGrid, Snake[SnakeLength], Snake[0]);
  UpdateScreenGridApple(ScreenGrid, Apple);
  DrawScreen(ScreenGrid);

  Delay2(1000000);
  while (1)
  {
    ControllerDir = ReadController();
    int moveSnakeOut = 0;
    int movDir;
    if ((ControllerDir + 2) % 4 == SnakeDir)
    {
      movDir = SnakeDir;
      MakeBadMelody();
    }else
    {
      MakeBadMelody();
      movDir = ControllerDir;
    }
    
    moveSnakeOut = MoveSnake(movDir, Snake, &SnakeLength, Apple);
    SnakeDir = movDir;

    if (moveSnakeOut == 2)
    {
      ResetApple(&Apple, Snake, SnakeLength);
      UpdateScreenGridApple(ScreenGrid, Apple);
    }
    if (moveSnakeOut == 1)
    {
      GameOver(3);
    }

    UpdateScreenGridSnake(ScreenGrid, Snake[SnakeLength], Snake[0]);
    DrawScreen(ScreenGrid);
    Delay2(1000000);
  }
}
