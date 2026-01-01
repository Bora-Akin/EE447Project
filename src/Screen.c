#include "Screen.h"

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
    return;
}
void CreateGameOverScreen(int gameScore)
{
    return;
}
void InitializeScreenGrid(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
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

void UpdateScreenGridSnake(bool screenGrid[SCREEN_WIDTH][SCREEN_HEIGHT], const Point oldSnakeTail, const Point newSnakeHead)
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
    screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 0] = false;
    screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 0] = false;
    screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 0] = false;

    screenGrid[1 + newSnakeHead.x * 4 + 0][1 + newSnakeHead.y * 4 + 1] = false;
    screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 1] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 1] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 1] = true;

    screenGrid[1 + newSnakeHead.x * 4 + 0][1 + newSnakeHead.y * 4 + 2] = false;
    screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 2] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 2] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 2] = true;

    screenGrid[1 + newSnakeHead.x * 4 + 0][1 + newSnakeHead.y * 4 + 3] = false;
    screenGrid[1 + newSnakeHead.x * 4 + 1][1 + newSnakeHead.y * 4 + 3] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 2][1 + newSnakeHead.y * 4 + 3] = true;
    screenGrid[1 + newSnakeHead.x * 4 + 3][1 + newSnakeHead.y * 4 + 3] = true;
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

// ---------------------------------------------------------------------------
// Nokia5110 Screen Init
// ---------------------------------------------------------------------------
void ScreenInit(void)
{
    SSI0_Init();

    // Reset Pulse (Low -> Wait -> High)
    GPIOA->DATA &= ~0x80; // PA7 Low (RST)
    Delay(50000);         // Wait
    GPIOA->DATA |= 0x80;  // PA7 High

    // Initialize Sequence
    ScreenWrite(0, 0x21); // Extended Commands
    ScreenWrite(0, 0xB8); // VOP (Contrast) - TRY CHANGING THIS (B0-BF)
    ScreenWrite(0, 0x04); // Temp Coefficient
    ScreenWrite(0, 0x13); // Bias 1:48
    ScreenWrite(0, 0x20); // Standard Commands
    ScreenWrite(0, 0x0C); // Normal Display Mode
}
// ---------------------------------------------------------------------------
// Nokia5110 Screen Write
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

// SSI0_Init
// Configures SSI0 and GPIO Port A with MANUAL Chip Select
// PA2(Clk), PA3(CS), PA5(Tx), PA6(DC), PA7(RST)
// ---------------------------------------------------------------------------
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
    GPIOA->PCTL &= 0x00F0F0FF; // Clear nibbles for PA7,6,5,3,2
    GPIOA->PCTL |= 0x00200200; // Set nibbles for PA5 and PA2 to 2

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

// Unused

void InitializeGameGrid(Block gameGrid[GAME_GRID_X][GAME_GRID_Y])
{
    // TODO: Can be changed to memset if it works
    for (int i = 0; i < GAME_GRID_X; i++)
    {
        for (int j = 0; j < GAME_GRID_Y; j++)
        {
            gameGrid[i][j] = BLANK;
        }
    }
}

void GameGridToScreenGrid(const Block inputGameGrid[GAME_GRID_X][GAME_GRID_Y], bool outputScreenGrid[SCREEN_WIDTH][SCREEN_HEIGHT])
{
    for (int i = 0; i < GAME_GRID_X; i++)
    {
        for (int j = 0; j < GAME_GRID_Y; j++)
        {
            // Border
            outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 0] = false;
            outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 0] = false;
            outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 0] = false;
            outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 0] = false;
            outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 1] = false;
            outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 2] = false;
            outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 3] = false;
            switch (inputGameGrid[i][j])
            {
            case BLANK:
                // up left of block
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 1] = false;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 1] = false;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 1] = false;
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 2] = false;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 2] = false;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 2] = false;
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 3] = false;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 3] = false;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 3] = false;
                break;
            case SNAKE:
                // up left of block
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 1] = true;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 1] = true;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 1] = true;
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 2] = true;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 2] = true;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 2] = true;
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 3] = true;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 3] = true;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 3] = true;
                // Border
                if (i > 0)
                {
                    if (inputGameGrid[i - 1][j] == SNAKE)
                    {
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 1] = true;
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 2] = true;
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 3] = true;
                    }
                    else
                    {
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 1] = false;
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 2] = false;
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 3] = false;
                    }
                }
                else
                {
                    outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 1] = false;
                    outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 2] = false;
                    outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 3] = false;
                }
                if (j > 0)
                {
                    if (inputGameGrid[i][j - 1] == SNAKE)
                    {
                        outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 0] = true;
                        outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 0] = true;
                        outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 0] = true;
                    }
                    else
                    {
                        outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 0] = false;
                        outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 0] = false;
                        outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 0] = false;
                    }
                }
                else
                {
                    outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 0] = false;
                    outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 0] = false;
                    outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 0] = false;
                }

                outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 0] = false;
                if (i > 0 && j > 0)
                {
                    if (inputGameGrid[i - 1][j - 1] == SNAKE && inputGameGrid[i - 1][j] && inputGameGrid[i][j - 1])
                    {
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 0] = true;
                    }
                    else
                    {
                        outputScreenGrid[i * 4 + 2 + 0][j * 4 + 2 + 0] = false;
                    }
                }

                break;
            case APPLE:
                // up left of block
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 1] = false;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 1] = true;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 1] = false;
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 2] = true;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 2] = false;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 2] = true;
                outputScreenGrid[i * 4 + 2 + 1][j * 4 + 2 + 3] = false;
                outputScreenGrid[i * 4 + 2 + 2][j * 4 + 2 + 3] = true;
                outputScreenGrid[i * 4 + 2 + 3][j * 4 + 2 + 3] = false;
                break;

            default:
                break;
            }
        }
    }
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
