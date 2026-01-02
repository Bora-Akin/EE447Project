#include <string.h>
#include "Screen.h"
#include "Game_Logic.h"
#include "buzzer.h"
#include "button_read.h"
#include "potantiometer.h"
#include "acc.h"

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
bool waitGame;
int GameSpeed;

bool IsStartButtonPressed()
{
  return IsPF4PressedDebounced();
}


void GameOver(int gameScore)
{
  MakeBadMelody();
  CreateGameOverScreen(gameScore, ScreenGrid);
  DrawScreen(ScreenGrid);
  // ScreenClear();

  while (!IsStartButtonPressed())
  {
    // Delay
  }
  return;
}

void StartScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
  MakeGoodMelody();
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
  // Initilaizes-----------------------------------------------------------
  //Accelerator Init
  ADXL345_Init();
  // Init potentiometer
  InitPotentiometer();
  // Init start button
  InitPF4();
  // Buzzer init
  InitBuzzer();
  // Screen Initialize
  ScreenInit();
  ScreenClear();
  ScreenWrite(0, 0x80);
  ScreenWrite(0, 0x40);
  //-----------------------------------------------------------------------
  do
  {
    // Start screen
    StartScreen(ScreenGrid);

    // Game Initialization
    isGameOver = false;
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
    while (!isGameOver)
    {
      waitGame = true;
      ControllerDir = InputDirection(SnakeDir);
      int moveSnakeOut = 0;
      int movDir;
      if ((ControllerDir + 2) % 4 == SnakeDir)
      {
        movDir = SnakeDir;
        MakeSound(100, 100);
      }
      else
      {
        movDir = ControllerDir;
        MakeSound(440, 100);
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
        isGameOver = true;
      }
      else
      {
        UpdateScreenGridSnake(ScreenGrid, Snake[SnakeLength], Snake[0]);
        DrawScreen(ScreenGrid);
      }
      while (waitGame)
      {
            }
    }

    GameOver(SnakeLength);
  } while (true);
}
