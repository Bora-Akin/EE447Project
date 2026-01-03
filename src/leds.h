#include "TM4C123GH6PM.h"
#include "Utils.h"

static int pwm_period = 100000;

int on_time;
int off_time;

extern int GameState;
extern int SnakeLength;

#define MAX_LENGTH (GAME_GRID_X * GAME_GRID_Y)

void LEDs_Init(void);
void TIMER4A_Handler(void);
void TurnOnBlueLed(void);
void TurnOnGreenLed(void);
void TurnOnRedLed(void);
void UpdateGreenLedTime(void);

void LEDs_Init(void)
{
    on_time = 0;
    off_time = pwm_period;

    volatile int *NVIC_EN2 = (volatile int *)0xE000E108;
    volatile int *NVIC_PRI17 = (volatile int *)0xE000E444;

    SYSCTL->RCGCGPIO |= 0x20;
    SYSCTL->RCGCTIMER |= 0x10;

    __ASM("NOP");
    __ASM("NOP");
    __ASM("NOP");

    GPIOF->DIR |= 0x0E; // pf1,pf2,pf3 config
    GPIOF->AFSEL &= ~0x0E;
    GPIOF->PCTL &= ~0x0000FFF0;
    GPIOF->AMSEL &= ~0x0E;
    GPIOF->DEN |= 0x0E;
    GPIOF->DATA &= ~0x0E;

    TIMER4->CTL &= ~0x01; // timer4 is used for the leds
    TIMER4->CFG = 0x04;
    TIMER4->TAMR = 0x02;
    TIMER4->TAILR = 0x7FFF;
    TIMER4->TAPR = 0;
    TIMER4->IMR = 0x01;

    *NVIC_PRI17 = (*NVIC_PRI17 & 0xFF00FFFF) | 0x00400000; // Priority 2 in bits 23:21
    *NVIC_EN2 |= 0x40;                                     // Enable IRQ 70, Bit 6

    // Enable Timer 4A
    TIMER4->CTL |= 0x01;
}

void TurnOnBlueLed(void)
{
    // only pf2 is on
    GPIOF->DATA &= ~0x0A; // turn off pf3 & pf1
    GPIOF->DATA |= 0x04;  // turn on pf2
    TIMER4->TAILR = pwm_period;

    TIMER4->CTL &= ~0x01; // Disable Timer 4A
}
void TurnOnGreenLed(void)
{
    GPIOF->DATA &= ~0x0E; // turns off pf2 & pf1 & pf3
    UpdateGreenLedTime();
    TIMER4->CTL |= 0x01; // Enable Timer 4A
}
void TurnOnRedLed(void)
{
    GPIOF->DATA &= ~0x0C; // turn off pf3 & pf2
    GPIOF->DATA |= 0x02;  // turn on pf1
    TIMER4->TAILR = pwm_period;
    TIMER4->CTL &= ~0x01; // Disable Timer 4A
}

void UpdateGreenLedTime(void)
{
    on_time = pwm_period * (SnakeLength - 8) / MAX_LENGTH; // maximum brightness is reached on maxLength score
    off_time = pwm_period - on_time;
}

void TIMER4A_Handler(void)
{
    TIMER4->ICR = 0x01;
    // If led was on set off time
    if (GPIOF->DATA & 0x08)
    {
        TIMER4->TAILR = off_time;
    }
    // If led was off set on time
    else
    {
        TIMER4->TAILR = on_time;
    }
    GPIOF->DATA ^= 0x08;
}