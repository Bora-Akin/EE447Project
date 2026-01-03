#include <string.h>
#include "Screen.h"
#include "Game_Logic.h"
#include "buzzer.h"
#include "button_read.h"
#include "potantiometer.h"
#include "acc.h"
#include "leds.h"

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
extern bool WaitGame;
int GameSpeed;

bool IsStartButtonPressedAndReleased()
{
  while (!IsPF4PressedDebounced())
  {
  }
  while (!IsPF4ReleasedDebounced())
  {
  }
  return true;
}

void GameOver(int gameScore)
{

  TurnOnRedLed();
  MakeBadMelody();
  CreateGameOverScreen(gameScore, ScreenGrid);
  DrawScreen(ScreenGrid);
  IsStartButtonPressedAndReleased();
  return;
}

void StartScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
  TurnOnBlueLed();
  MakeGoodMelody();
  CreateStartScreen(screenGrid);
  DrawScreen(screenGrid);
  IsStartButtonPressedAndReleased();
  srand(ReadPot());
  return;
}

int main(void)
{
  // Initilaizes-----------------------------------------------------------
  // LED
  LEDs_Init();
  // Accelerator Init
  ADXL345_Init();
  // Init potentiometer
  InitPotentiometer();
  // Init start button
  InitPF4();
  // Sound init
  InitBuzzer();
  // Screen Initialize
  ScreenInit();
  ScreenClear();
  ScreenWrite(0, 0x80);
  ScreenWrite(0, 0x40);
  //-----------------------------------------------------------------------
  // Start screen
  StartScreen(ScreenGrid);

  do
  {
    // Game Initialization
    isGameOver = false;
    Snake[0].x = 8;
    Snake[0].y = 5;
    Snake[1].x = 7;
    Snake[1].y = 5;
    Snake[2].x = 6;
    Snake[2].y = 5;
    Snake[3].x = 5;
    Snake[3].y = 5;
    Snake[4].x = 4;
    Snake[4].y = 5;
    Snake[5].x = 3;
    Snake[5].y = 5;
    Snake[6].x = 2;
    Snake[6].y = 5;
    Snake[7].x = 1;
    Snake[7].y = 5;
    SnakeLength = 8;
    SnakeDir = 1;
    ControllerDir = 1;
    int moveSnakeOut = 0;

    ResetApple(&Apple, Snake, SnakeLength);
    TurnOnGreenLed();
    InitializeScreenGrid(ScreenGrid, Snake, SnakeLength);
    UpdateScreenGridSnake(ScreenGrid, Snake[SnakeLength], Snake[0], Snake);
    UpdateScreenGridApple(ScreenGrid, Apple);
    DrawScreen(ScreenGrid);

    Delay2(1000000);
    while (!isGameOver)
    {
      WaitGame = true;
      ControllerDir = InputDirection(SnakeDir);
      moveSnakeOut = 0;
      if ((ControllerDir + 2) % 4 == SnakeDir)
      {
        MakeSound(100, 100);
      }
      else if (SnakeDir != ControllerDir)
      {
        SnakeDir = ControllerDir;
        MakeSound(440, 100);
      }

      moveSnakeOut = MoveSnake(SnakeDir, Snake, &SnakeLength, Apple);

      if (moveSnakeOut == 2)
      {
        MakeAppleMelody();
        ResetApple(&Apple, Snake, SnakeLength);
        UpdateScreenGridApple(ScreenGrid, Apple);
        UpdateGreenLedTime();
      }
      if (moveSnakeOut == 1)
      {
        isGameOver = true;
      }
      else
      {
        UpdateScreenGridSnake(ScreenGrid, Snake[SnakeLength], Snake[0], Snake);
        DrawScreen(ScreenGrid);
      }
      while (WaitGame && !isGameOver)
      {
      }
    }
    GameOver(SnakeLength);
  } while (true);
}
