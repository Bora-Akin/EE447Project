#include "Screen.h"


    // Struct StructName ArrayName[ROWS][COLS];
    // Grid of the game
    enum Block gameGrid[GAME_GRID_X][GAME_GRID_Y];
    // Pixels in the screen
    bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT];

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

		InitializeGameGrid(gameGrid);
    gameGrid[0][0] = SNAKE;
    gameGrid[3][3] = SNAKE;
    gameGrid[3][4] = SNAKE;
    gameGrid[3][5] = SNAKE;
    gameGrid[3][6] = APPLE;
		InitializeScreenGrid(screenGrid);
		GameGridToScreenGrid(gameGrid,screenGrid);
		ScreenWriteGrid(screenGrid);
	
		int x = 0;
		int y = 0;
    // Loop forever drawing a pattern
    while (1)
    {
		GameGridToScreenGrid(gameGrid,screenGrid);
		ScreenWriteGrid(screenGrid);
    Delay(400000);
    gameGrid[x][y] = SNAKE;
		x++;
		if(x == GAME_GRID_X){
			x = 0;
			y++;
		}
	/*
			
        // Draw Diagonal Line Pattern
        for (int i = 0; i < 84; i++)
        {
            // Creates a shifting bit pattern
            ScreenWrite(1, (1 << (i % 8)));
        }

        // Wait so you can see if the screen resets or flickers
        Delay(400000);

        // Invert screen command (Test if commands are working)
        ScreenWrite(0, 0x0D); // Inverse Video
        Delay(400000);
        ScreenWrite(0, 0x0C); // Normal Video
		*/
    }
}