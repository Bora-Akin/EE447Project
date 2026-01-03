#include "Screen.h"
#include <stdbool.h>

void Delay(uint32_t n)
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

void CreateStartScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
    // Gemini was used to create the start screen

    // Clear the entire grid first
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            screenGrid[x][y] = false;
        }
    }

    // ==========================================
    // Draw Title: "SNAKE" (Large, Bold Letters)
    // ==========================================
    // Starting Y position for the title row
    int titleY = 8;

    // --- Draw 'S' ---
    int sx = 18; // Starting X for S
    // Top bar
    screenGrid[sx + 1][titleY + 0] = true;
    screenGrid[sx + 2][titleY + 0] = true;
    screenGrid[sx + 3][titleY + 0] = true;
    // Left side top
    screenGrid[sx + 0][titleY + 1] = true;
    screenGrid[sx + 0][titleY + 2] = true;
    // Middle curve
    screenGrid[sx + 1][titleY + 3] = true;
    screenGrid[sx + 2][titleY + 3] = true;
    // Right side bottom
    screenGrid[sx + 3][titleY + 4] = true;
    screenGrid[sx + 3][titleY + 5] = true;
    // Bottom bar
    screenGrid[sx + 0][titleY + 6] = true;
    screenGrid[sx + 1][titleY + 6] = true;
    screenGrid[sx + 2][titleY + 6] = true;

    // --- Draw 'N' ---
    int nx = 28; // Starting X for N
    // Left vertical line
    for (int i = 0; i <= 6; i++)
        screenGrid[nx + 0][titleY + i] = true;
    // Diagonal line
    screenGrid[nx + 1][titleY + 2] = true;
    screenGrid[nx + 2][titleY + 3] = true;
    screenGrid[nx + 3][titleY + 4] = true;
    // Right vertical line
    for (int i = 0; i <= 6; i++)
        screenGrid[nx + 4][titleY + i] = true;

    // --- Draw 'A' ---
    int ax = 38; // Starting X for A
    // Top point
    screenGrid[ax + 2][titleY + 0] = true;
    screenGrid[ax + 1][titleY + 1] = true;
    screenGrid[ax + 3][titleY + 1] = true;
    // Middle bar
    screenGrid[ax + 1][titleY + 3] = true;
    screenGrid[ax + 2][titleY + 3] = true;
    screenGrid[ax + 3][titleY + 3] = true;
    // Side legs
    for (int i = 2; i <= 6; i++)
        screenGrid[ax + 0][titleY + i] = true;
    for (int i = 2; i <= 6; i++)
        screenGrid[ax + 4][titleY + i] = true;

    // --- Draw 'K' ---
    int kx = 48;
    // Left vertical line
    for (int i = 0; i <= 6; i++)
        screenGrid[kx + 0][titleY + i] = true;
    // Top diagonal notch
    screenGrid[kx + 3][titleY + 0] = true;
    screenGrid[kx + 2][titleY + 1] = true;
    screenGrid[kx + 1][titleY + 2] = true;
    // Middle join
    screenGrid[kx + 1][titleY + 3] = true;
    // Bottom diagonal leg
    screenGrid[kx + 2][titleY + 4] = true;
    screenGrid[kx + 3][titleY + 5] = true;
    screenGrid[kx + 4][titleY + 6] = true;

    // --- Draw 'E' ---
    int ex = 58;
    // Left vertical line
    for (int i = 0; i <= 6; i++)
        screenGrid[ex + 0][titleY + i] = true;
    // Top bar
    for (int i = 0; i <= 3; i++)
        screenGrid[ex + i][titleY + 0] = true;
    // Middle bar (shorter)
    for (int i = 0; i <= 2; i++)
        screenGrid[ex + i][titleY + 3] = true;
    // Bottom bar
    for (int i = 0; i <= 3; i++)
        screenGrid[ex + i][titleY + 6] = true;

    // ==========================================================
    // Draw Subtitle: "PRESS BUTTON" (Smaller letters underneath)
    // ==========================================================
    // Due to space constraints and tedium, I shortened the text slightly
    // and used very small (3x5 pixel) letters.

    int subY = 30; // Y position for subtitle row

    // P (at x=10)
    for (int i = 0; i < 5; i++)
        screenGrid[10][subY + i] = true;
    screenGrid[11][subY] = true;
    screenGrid[12][subY + 1] = true;
    screenGrid[11][subY + 2] = true;

    // R (at x=14)
    for (int i = 0; i < 5; i++)
        screenGrid[14][subY + i] = true;
    screenGrid[15][subY] = true;
    screenGrid[16][subY + 1] = true;
    screenGrid[15][subY + 2] = true;
    screenGrid[16][subY + 3] = true;
    screenGrid[16][subY + 4] = true;

    // E (at x=18)
    for (int i = 0; i < 5; i++)
        screenGrid[18][subY + i] = true;
    screenGrid[19][subY] = true;
    screenGrid[20][subY] = true;
    screenGrid[19][subY + 2] = true;
    screenGrid[19][subY + 4] = true;
    screenGrid[20][subY + 4] = true;

    // S (at x=22)
    screenGrid[22][subY] = true;
    screenGrid[23][subY] = true;
    screenGrid[24][subY] = true;
    screenGrid[22][subY + 1] = true;
    screenGrid[23][subY + 2] = true;
    screenGrid[24][subY + 3] = true;
    screenGrid[22][subY + 4] = true;
    screenGrid[23][subY + 4] = true;
    screenGrid[24][subY + 4] = true;

    // S (at x=26) - Same as above
    screenGrid[26][subY] = true;
    screenGrid[27][subY] = true;
    screenGrid[28][subY] = true;
    screenGrid[26][subY + 1] = true;
    screenGrid[27][subY + 2] = true;
    screenGrid[28][subY + 3] = true;
    screenGrid[26][subY + 4] = true;
    screenGrid[27][subY + 4] = true;
    screenGrid[28][subY + 4] = true;

    // -- Space at x=30, 31 --

    // B (at x=32)
    for (int i = 0; i < 5; i++)
        screenGrid[32][subY + i] = true;
    screenGrid[33][subY] = true;
    screenGrid[33][subY + 2] = true;
    screenGrid[33][subY + 4] = true;
    screenGrid[34][subY + 1] = true;
    screenGrid[34][subY + 3] = true;

    // U (at x=36)
    for (int i = 0; i < 4; i++)
        screenGrid[36][subY + i] = true;
    for (int i = 0; i < 4; i++)
        screenGrid[38][subY + i] = true;
    screenGrid[37][subY + 4] = true;

    // T (at x=40)
    for (int i = 0; i < 3; i++)
        screenGrid[40 + i][subY] = true;
    for (int i = 1; i < 5; i++)
        screenGrid[41][subY + i] = true;

    // T (at x=44)
    for (int i = 0; i < 3; i++)
        screenGrid[44 + i][subY] = true;
    for (int i = 1; i < 5; i++)
        screenGrid[45][subY + i] = true;

    // O (at x=48)
    for (int i = 1; i < 4; i++)
        screenGrid[48][subY + i] = true;
    for (int i = 1; i < 4; i++)
        screenGrid[50][subY + i] = true;
    screenGrid[49][subY] = true;
    screenGrid[49][subY + 4] = true;

    // N (at x=52)
    for (int i = 0; i < 5; i++)
        screenGrid[52][subY + i] = true;
    screenGrid[53][subY + 1] = true;
    screenGrid[53][subY + 2] = true;
    for (int i = 0; i < 5; i++)
        screenGrid[54][subY + i] = true;

    // Draw a simple underline decoration
    for (int x = 10; x < 65; x++)
    {
        screenGrid[x][subY + 6] = true;
    }

    return;
}

void CreateGameOverScreen(int gameScore, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
    // Game Over screen was generated using Gemini

    // Clear the screen
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            screenGrid[x][y] = false;
        }
    }

    // ==========================================
    // 1. Draw "GAME" (Y = 4)
    // ==========================================
    int gy = 4;

    // G (x=24)
    for (int i = 1; i < 6; i++)
        screenGrid[24][gy + i] = true; // Left
    screenGrid[25][gy] = true;
    screenGrid[26][gy] = true;
    screenGrid[27][gy] = true; // Top
    screenGrid[25][gy + 6] = true;
    screenGrid[26][gy + 6] = true;
    screenGrid[27][gy + 6] = true; // Bottom
    screenGrid[27][gy + 3] = true;
    screenGrid[27][gy + 4] = true;
    screenGrid[27][gy + 5] = true; // Hook
    screenGrid[26][gy + 3] = true; // Inward dash

    // A (x=30)
    for (int i = 2; i < 7; i++)
        screenGrid[30][gy + i] = true;
    for (int i = 2; i < 7; i++)
        screenGrid[34][gy + i] = true;
    screenGrid[31][gy + 1] = true;
    screenGrid[33][gy + 1] = true;
    screenGrid[32][gy] = true;
    screenGrid[31][gy + 3] = true;
    screenGrid[32][gy + 3] = true;
    screenGrid[33][gy + 3] = true;

    // M (x=36)
    for (int i = 0; i < 7; i++)
        screenGrid[36][gy + i] = true;
    for (int i = 0; i < 7; i++)
        screenGrid[40][gy + i] = true;
    screenGrid[37][gy + 1] = true;
    screenGrid[38][gy + 2] = true;
    screenGrid[39][gy + 1] = true;

    // E (x=42)
    for (int i = 0; i < 7; i++)
        screenGrid[42][gy + i] = true;
    for (int i = 0; i < 4; i++)
        screenGrid[42 + i][gy] = true; // Top
    for (int i = 0; i < 3; i++)
        screenGrid[42 + i][gy + 3] = true; // Mid
    for (int i = 0; i < 4; i++)
        screenGrid[42 + i][gy + 6] = true; // Bot

    // ==========================================
    // 2. Draw "OVER" (Y = 14)
    // ==========================================
    int oy = 14;

    // O (x=24)
    for (int i = 1; i < 6; i++)
        screenGrid[24][oy + i] = true;
    for (int i = 1; i < 6; i++)
        screenGrid[28][oy + i] = true;
    screenGrid[25][oy] = true;
    screenGrid[26][oy] = true;
    screenGrid[27][oy] = true;
    screenGrid[25][oy + 6] = true;
    screenGrid[26][oy + 6] = true;
    screenGrid[27][oy + 6] = true;

    // V (x=30)
    for (int i = 0; i < 5; i++)
        screenGrid[30][oy + i] = true;
    for (int i = 0; i < 5; i++)
        screenGrid[34][oy + i] = true;
    screenGrid[31][oy + 5] = true;
    screenGrid[33][oy + 5] = true;
    screenGrid[32][oy + 6] = true;

    // E (x=36)
    for (int i = 0; i < 7; i++)
        screenGrid[36][oy + i] = true;
    for (int i = 0; i < 4; i++)
        screenGrid[36 + i][oy] = true;
    for (int i = 0; i < 3; i++)
        screenGrid[36 + i][oy + 3] = true;
    for (int i = 0; i < 4; i++)
        screenGrid[36 + i][oy + 6] = true;

    // R (x=42)
    for (int i = 0; i < 7; i++)
        screenGrid[42][oy + i] = true;
    screenGrid[43][oy] = true;
    screenGrid[44][oy] = true;
    screenGrid[45][oy + 1] = true;
    screenGrid[45][oy + 2] = true;
    screenGrid[44][oy + 3] = true;
    screenGrid[43][oy + 3] = true;
    screenGrid[44][oy + 4] = true;
    screenGrid[45][oy + 5] = true;
    screenGrid[46][oy + 6] = true;

    // ==========================================
    // 3. Draw "SCORE:" (Y = 30) (Small Font)
    // ==========================================
    int sy = 30;

    // S (x=10)
    screenGrid[10][sy] = 1;
    screenGrid[11][sy] = 1;
    screenGrid[12][sy] = 1;
    screenGrid[10][sy + 1] = 1;
    screenGrid[10][sy + 2] = 1;
    screenGrid[11][sy + 2] = 1;
    screenGrid[12][sy + 2] = 1;
    screenGrid[12][sy + 3] = 1;
    screenGrid[10][sy + 4] = 1;
    screenGrid[11][sy + 4] = 1;
    screenGrid[12][sy + 4] = 1;

    // C (x=14)
    for (int i = 0; i < 5; i++)
        screenGrid[14][sy + i] = 1;
    screenGrid[15][sy] = 1;
    screenGrid[16][sy] = 1;
    screenGrid[15][sy + 4] = 1;
    screenGrid[16][sy + 4] = 1;

    // O (x=18)
    for (int i = 0; i < 5; i++)
        screenGrid[18][sy + i] = 1;
    for (int i = 0; i < 5; i++)
        screenGrid[20][sy + i] = 1;
    screenGrid[19][sy] = 1;
    screenGrid[19][sy + 4] = 1;

    // R (x=22)
    for (int i = 0; i < 5; i++)
        screenGrid[22][sy + i] = 1;
    screenGrid[23][sy] = 1;
    screenGrid[24][sy] = 1;
    screenGrid[24][sy + 1] = 1;
    screenGrid[23][sy + 2] = 1;
    screenGrid[24][sy + 2] = 1;
    screenGrid[24][sy + 3] = 1;
    screenGrid[24][sy + 4] = 1;

    // E (x=26)
    for (int i = 0; i < 5; i++)
        screenGrid[26][sy + i] = 1;
    screenGrid[27][sy] = 1;
    screenGrid[28][sy] = 1;
    screenGrid[27][sy + 2] = 1;
    screenGrid[28][sy + 2] = 1;
    screenGrid[27][sy + 4] = 1;
    screenGrid[28][sy + 4] = 1;

    // : (x=30)
    screenGrid[30][sy + 1] = true;
    screenGrid[30][sy + 3] = true;

    // ==========================================
    // 4. Draw The Number (Y = 30, X starts at 34)
    // ==========================================

    // Break score into digits (Up to 999)
    if (gameScore > 999)
        gameScore = 999;
    int hundreds = gameScore / 100;
    int tens = (gameScore / 10) % 10;
    int ones = gameScore % 10;

    int digits[3] = {hundreds, tens, ones};
    int startX = 34;

    // Loop through the 3 digits
    for (int k = 0; k < 3; k++)
    {
        int d = digits[k];
        int dx = startX + (k * 5); // Shift right by 5 pixels for each digit

        // Skip leading zeros (optional, but looks better)
        // If score is 0, print "000" or just "0" depending on preference.
        // This simple version prints "005" for 5.

        switch (d)
        {
        case 0:
            for (int i = 0; i < 5; i++)
            {
                screenGrid[dx][sy + i] = 1;
                screenGrid[dx + 2][sy + i] = 1;
            }
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            break;
        case 1:
            for (int i = 0; i < 5; i++)
                screenGrid[dx + 1][sy + i] = 1;
            screenGrid[dx][sy + 1] = 1;
            screenGrid[dx][sy + 4] = 1;
            screenGrid[dx + 2][sy + 4] = 1;
            break;
        case 2:
            screenGrid[dx][sy] = 1;
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 2][sy] = 1;
            screenGrid[dx + 2][sy + 1] = 1;
            screenGrid[dx][sy + 2] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 2][sy + 2] = 1;
            screenGrid[dx][sy + 3] = 1;
            screenGrid[dx][sy + 4] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            screenGrid[dx + 2][sy + 4] = 1;
            break;
        case 3:
            screenGrid[dx][sy] = 1;
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 2][sy] = 1;
            screenGrid[dx + 2][sy + 1] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 2][sy + 2] = 1;
            screenGrid[dx + 2][sy + 3] = 1;
            screenGrid[dx][sy + 4] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            screenGrid[dx + 2][sy + 4] = 1;
            break;
        case 4:
            screenGrid[dx][sy] = 1;
            screenGrid[dx][sy + 1] = 1;
            screenGrid[dx][sy + 2] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 2][sy + 2] = 1;
            for (int i = 0; i < 5; i++)
                screenGrid[dx + 2][sy + i] = 1;
            break;
        case 5:
            screenGrid[dx][sy] = 1;
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 2][sy] = 1;
            screenGrid[dx][sy + 1] = 1;
            screenGrid[dx][sy + 2] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 2][sy + 2] = 1;
            screenGrid[dx + 2][sy + 3] = 1;
            screenGrid[dx][sy + 4] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            screenGrid[dx + 2][sy + 4] = 1;
            break;
        case 6:
            screenGrid[dx][sy] = 1;
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 2][sy] = 1;
            screenGrid[dx][sy + 1] = 1;
            screenGrid[dx][sy + 2] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 2][sy + 2] = 1;
            screenGrid[dx][sy + 3] = 1;
            screenGrid[dx + 2][sy + 3] = 1;
            screenGrid[dx][sy + 4] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            screenGrid[dx + 2][sy + 4] = 1;
            break;
        case 7:
            screenGrid[dx][sy] = 1;
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 2][sy] = 1;
            screenGrid[dx + 2][sy + 1] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 1][sy + 3] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            break;
        case 8:
            for (int i = 0; i < 5; i++)
            {
                screenGrid[dx][sy + i] = 1;
                screenGrid[dx + 2][sy + i] = 1;
            }
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            break;
        case 9:
            screenGrid[dx][sy] = 1;
            screenGrid[dx + 1][sy] = 1;
            screenGrid[dx + 2][sy] = 1;
            screenGrid[dx][sy + 1] = 1;
            screenGrid[dx + 2][sy + 1] = 1;
            screenGrid[dx][sy + 2] = 1;
            screenGrid[dx + 1][sy + 2] = 1;
            screenGrid[dx + 2][sy + 2] = 1;
            screenGrid[dx + 2][sy + 3] = 1;
            screenGrid[dx][sy + 4] = 1;
            screenGrid[dx + 1][sy + 4] = 1;
            screenGrid[dx + 2][sy + 4] = 1;
            break;
        }
    }
}
void InitializeScreenGrid(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], Point *snake, int snakeLength)
{
    // TODO: Can be changed to memset if it works
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            screenGrid[x][y] = false;
        }
    }
    // memset(screenGrid, 0, sizeof(screenGrid));

    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        screenGrid[i][0] = true;
        screenGrid[i][SCREEN_HEIGHT - 1] = true;
    }
    for (int j = 0; j < SCREEN_HEIGHT; j++)
    {
        screenGrid[0][j] = true;
        screenGrid[SCREEN_WIDTH - 1][j] = true;
    }

    for (int i = 0; i < snakeLength; i++)
    {
        // Draw the new head
        screenGrid[1 + snake[i].x * 4 + 0][1 + snake[i].y * 4 + 0] = false; // Top left of snake, goes row by row from left to right

        screenGrid[1 + snake[i].x * 4 + 1][1 + snake[i].y * 4 + 0] = false;
        screenGrid[1 + snake[i].x * 4 + 2][1 + snake[i].y * 4 + 0] = false;
        screenGrid[1 + snake[i].x * 4 + 3][1 + snake[i].y * 4 + 0] = false;

        screenGrid[1 + snake[i].x * 4 + 0][1 + snake[i].y * 4 + 1] = true;
        screenGrid[1 + snake[i].x * 4 + 1][1 + snake[i].y * 4 + 1] = true;
        screenGrid[1 + snake[i].x * 4 + 2][1 + snake[i].y * 4 + 1] = true;
        screenGrid[1 + snake[i].x * 4 + 3][1 + snake[i].y * 4 + 1] = true;

        screenGrid[1 + snake[i].x * 4 + 0][1 + snake[i].y * 4 + 2] = true;
        screenGrid[1 + snake[i].x * 4 + 1][1 + snake[i].y * 4 + 2] = true;
        screenGrid[1 + snake[i].x * 4 + 2][1 + snake[i].y * 4 + 2] = true;
        screenGrid[1 + snake[i].x * 4 + 3][1 + snake[i].y * 4 + 2] = true;

        screenGrid[1 + snake[i].x * 4 + 0][1 + snake[i].y * 4 + 3] = true;
        screenGrid[1 + snake[i].x * 4 + 1][1 + snake[i].y * 4 + 3] = true;
        screenGrid[1 + snake[i].x * 4 + 2][1 + snake[i].y * 4 + 3] = true;
        screenGrid[1 + snake[i].x * 4 + 3][1 + snake[i].y * 4 + 3] = true;
    }
}
void DrawScreen(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
    // Reset Cursor to top left
    ScreenWrite(0, 0x80);
    ScreenWrite(0, 0x40);

    for (int page = 0; page < 6; page++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            uint8_t byteToSend = ExtractBlock(x, page, screenGrid);
            ScreenWrite(1, byteToSend);
        }
    }
}

void UpdateScreenGridSnake(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point oldSnakeTail, const Point newSnakeHead, const Point *snake)
{
    // Erase the old tail
    screenGrid[1 + oldSnakeTail.x * 4 + 0][1 + oldSnakeTail.y * 4 + 0] = false; // Top left of snake, goes row by row from left to right
    screenGrid[1 + oldSnakeTail.x * 4 + 1][1 + oldSnakeTail.y * 4 + 0] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 2][1 + oldSnakeTail.y * 4 + 0] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 3][1 + oldSnakeTail.y * 4 + 0] = false;

    screenGrid[1 + oldSnakeTail.x * 4 + 0][1 + oldSnakeTail.y * 4 + 1] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 1][1 + oldSnakeTail.y * 4 + 1] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 2][1 + oldSnakeTail.y * 4 + 1] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 3][1 + oldSnakeTail.y * 4 + 1] = false;

    screenGrid[1 + oldSnakeTail.x * 4 + 0][1 + oldSnakeTail.y * 4 + 2] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 1][1 + oldSnakeTail.y * 4 + 2] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 2][1 + oldSnakeTail.y * 4 + 2] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 3][1 + oldSnakeTail.y * 4 + 2] = false;

    screenGrid[1 + oldSnakeTail.x * 4 + 0][1 + oldSnakeTail.y * 4 + 3] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 1][1 + oldSnakeTail.y * 4 + 3] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 2][1 + oldSnakeTail.y * 4 + 3] = false;
    screenGrid[1 + oldSnakeTail.x * 4 + 3][1 + oldSnakeTail.y * 4 + 3] = false;

    // Draw the new head
    screenGrid[1 + newSnakeHead.x * 4 + 0][1 + newSnakeHead.y * 4 + 0] = false; // Top left of snake, goes row by row from left to right

    screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 1] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 1] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 1] = true;

    screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 2] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 2] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 2] = true;

    screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 3] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 3] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 3] = true;

    // For continious snake
    if (snake[0].x - 1 == snake[1].x)
    {
        screenGrid[1 + newSnakeHead.x * 4 + 0][1 + newSnakeHead.y * 4 + 1] = true;
        screenGrid[1 + newSnakeHead.x * 4 + 0][1 + newSnakeHead.y * 4 + 2] = true;
        screenGrid[1 + newSnakeHead.x * 4 + 0][1 + newSnakeHead.y * 4 + 3] = true;
    }
    else if (snake[0].x + 1 == snake[1].x)
    {
        screenGrid[1 + snake[1].x * 4 + 0][1 + snake[1].y * 4 + 1] = true;
        screenGrid[1 + snake[1].x * 4 + 0][1 + snake[1].y * 4 + 2] = true;
        screenGrid[1 + snake[1].x * 4 + 0][1 + snake[1].y * 4 + 3] = true;
    }
    else if (snake[0].y - 1 == snake[1].y)
    {
        screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 0] = true;
        screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 0] = true;
        screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 0] = true;
    }
    else if (snake[0].y + 1 == snake[1].y)
    {
        screenGrid[1 + snake[1].x * 4 + 1][1 + snake[1].y * 4 + 0] = true;
        screenGrid[1 + snake[1].x * 4 + 2][1 + snake[1].y * 4 + 0] = true;
        screenGrid[1 + snake[1].x * 4 + 3][1 + snake[1].y * 4 + 0] = true;
    }
}
void UpdateScreenGridApple(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point Apple)
{
    screenGrid[1 + Apple.x * 4 + 0][1 + Apple.y * 4 + 0] = false; // Top left of apple, goes row by row from left to right
    screenGrid[1 + Apple.x * 4 + 1][1 + Apple.y * 4 + 0] = false;
    screenGrid[1 + Apple.x * 4 + 2][1 + Apple.y * 4 + 0] = false;
    screenGrid[1 + Apple.x * 4 + 3][1 + Apple.y * 4 + 0] = false;

    screenGrid[1 + Apple.x * 4 + 0][1 + Apple.y * 4 + 1] = false;
    screenGrid[1 + Apple.x * 4 + 1][1 + Apple.y * 4 + 1] = false;
    screenGrid[1 + Apple.x * 4 + 2][1 + Apple.y * 4 + 1] = true;
    screenGrid[1 + Apple.x * 4 + 3][1 + Apple.y * 4 + 1] = false;

    screenGrid[1 + Apple.x * 4 + 0][1 + Apple.y * 4 + 2] = false;
    screenGrid[1 + Apple.x * 4 + 1][1 + Apple.y * 4 + 2] = true;
    screenGrid[1 + Apple.x * 4 + 2][1 + Apple.y * 4 + 2] = false;
    screenGrid[1 + Apple.x * 4 + 3][1 + Apple.y * 4 + 2] = true;

    screenGrid[1 + Apple.x * 4 + 0][1 + Apple.y * 4 + 3] = false;
    screenGrid[1 + Apple.x * 4 + 1][1 + Apple.y * 4 + 3] = false;
    screenGrid[1 + Apple.x * 4 + 2][1 + Apple.y * 4 + 3] = true;
    screenGrid[1 + Apple.x * 4 + 3][1 + Apple.y * 4 + 3] = false;
}

// Nokia screen init
void ScreenInit(void)
{
    SSI0_Init();

    // Reset the screen
    GPIOA->DATA &= ~0x80; // PA7 Low
    Delay(50000);         // Wait
    GPIOA->DATA |= 0x80;  // PA7 High

    // Initialize Sequence
    ScreenWrite(0, 0x21); // Extended Commands
    ScreenWrite(0, 0xBF); // VOP (Contrast) - TRY CHANGING THIS (B0-BF)
    ScreenWrite(0, 0x04); // Temp Coefficient
    ScreenWrite(0, 0x13); // Bias 1:48
    ScreenWrite(0, 0x20); // Standard Commands
    ScreenWrite(0, 0x0C); // Normal Display Mode
}

// Nokia Screen Write
// type: command->0, data->1
void ScreenWrite(uint8_t type, uint8_t message)
{
    //
    while ((SSI0->SR & 0x02) == 0)
    {
    }; // Wait until SSI is ready to transmit
    // Set to data or command
    if (type == 0)
    {
        GPIOA->DATA &= ~0x40; // PA6 Low = Command
    }
    else
    {
        GPIOA->DATA |= 0x40; // PA6 High = Data
    }
    GPIOA->DATA &= ~0x08; // Manual CS: Pull PA3 Low to start transmission
    SSI0->DR = message;
    while (SSI0->SR & 0x10)
    {
    }; // Wait for transmission to complete (Busy Bit = 0)
    GPIOA->DATA |= 0x08; // Manual CS: Push PA3 High to end transmission
}
// Helper to clear screen
void ScreenClear(void)
{
    int i;
    ScreenWrite(0, 0x80); // X=0
    ScreenWrite(0, 0x40); // Y=0
    for (i = 0; i < 504; i++)
    {
        ScreenWrite(1, 0x00);
    }
}

// SSI0 Init
// PA2(Clk), PA3(CS), PA5(Tx), PA6(DC), PA7(RST)
void SSI0_Init(void)
{
    // Start Clks
    SYSCTL->RCGCGPIO |= 0x01; // Enable Clock for GPIO Port A
    while ((SYSCTL->PRGPIO & 0x01) == 0)
    {
    }; // Wait for GPIO Port A to be ready
    SYSCTL->RCGCSSI |= 0x01; // Enable Clock for SSI0
    while ((SYSCTL->PRSSI & 0x01) == 0)
    {
    }; // Wait for SSI0 to be ready

    // GPIO A Config
    GPIOA->DEN |= 0xEC;    // Binary: 1110 1100 //PA2 PA3 PA5 PA6 PA7
    GPIOA->DIR |= 0xEC;    // Binary: 1110 1100 //PA2 PA3 PA5 PA6 PA7
    GPIOA->AFSEL |= 0x24;  // Binary: 0010 0100 //Enable for PA2 PA5
    GPIOA->AFSEL &= ~0xC8; // Disable for PA3 PA6 PA7
    // Set PMCx to 2 for PA2 and PA5. Clear others to 0.
    GPIOA->PCTL &= 0x00F0F0FF; // Clear  for PA7,6,5,3,2
    GPIOA->PCTL |= 0x00200200; // Set for PA5 and PA2 to 2

    // SSI Configuration
    SSI0->CR1 &= ~0x02;                           // Disable SSI during configuration
    SSI0->CPSR = 50;                              // Clk Rate Using Divisor 50 to ensure we don't exceed Nokia's 4MHz limit
    SSI0->CR0 &= ~0x0000FF00;                     // SCR = 0
    SSI0->CR0 &= ~0x000000C0;                     // SPO=0, SPH=0
    SSI0->CR0 &= ~0x00000030;                     // FRF = Freescale
    SSI0->CR0 = (SSI0->CR0 & ~0x0000000F) + 0x07; // Set Data Size to 8-bit
    SSI0->CR1 |= 0x02;                            // Enable SSI
    GPIOA->DATA |= 0x08;                          // Set CS (PA3) High (Idle state)
}

uint8_t ExtractBlock(int x, int pageIndex, bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
    uint8_t data = 0x00;

    // A "page" is a group of 8 vertical pixels.
    // pageIndex 0 covers y=0 to y=7
    // pageIndex 1 covers y=8 to y=15, etc.
    int yBase = pageIndex * 8;

    for (int bit = 0; bit < 8; bit++)
    {
        // Calculate the actual Y coordinate in the bool grid
        int currentY = yBase + bit;

        // Check our bool grid.
        // IF the pixel is ON (true), we set the corresponding bit.
        if (screenGrid[x][currentY])
        {
            // Shift a '1' to the correct position (0-7) and OR it in
            data |= (1 << bit);
        }
    }

    return data;
}
