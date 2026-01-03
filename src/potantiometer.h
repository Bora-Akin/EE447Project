#include "TM4C123GH6PM.h"
extern int ReadPot(void);

bool WaitGame;
void InitPotentiometer(void);
uint16_t adc0In(void);

void InitPotentiometer(void)
{
    volatile int *NVIC_EN0 = (volatile int *)0xE000E100;
    volatile int *NVIC_PRI4 = (volatile int *)0xE000E410;

    // CLK setup
    SYSCTL->RCGCGPIO |= 0x10;  // PE
    SYSCTL->RCGCTIMER |= 0x01; // Enable Timer 0
    SYSCTL->RCGCADC |= 0x01;   // ADC0

    // Wait for clocks to stabilize
    while ((SYSCTL->PRADC & 0x01) == 0)
        ;
    while ((SYSCTL->PRGPIO & 0x10) == 0)
        ;
    while ((SYSCTL->PRTIMER & 0x01) == 0)
        ;

    // GPIO PE3
    GPIOE->DIR &= ~0x08;  // In
    GPIOE->AFSEL |= 0x08; // yes alternate function
    GPIOE->AMSEL |= 0x08; // Analog input
    GPIOE->DEN &= ~0x08;  // no digital

    // ADC setup
    ADC0->ACTSS &= ~0x08;
    ADC0->PC = 0x01;
    ADC0->EMUX &= ~0xF000;
    ADC0->SSMUX3 = 0x00;
    ADC0->SSCTL3 = 0x0006;
    ADC0->ACTSS |= 0x08;

    // TIMER0 for game speed
    TIMER0->CTL &= ~0x01;
    TIMER0->CFG = 0x00;              // 32 bit mode
    TIMER0->TAMR = 0x02;             // Periodic mode
    TIMER0->TAPR = 0;                // no prescale
    TIMER0->TAILR = 3200000 + (ReadPot() * 7033);
    TIMER0->IMR |= 0x01;             // Enable Interrupt on Timeout

    // Timer0A is interrupt 19
    *NVIC_PRI4 &= 0x00FFFFFF; // Clear interrupt 19 priority
    *NVIC_PRI4 |= 0x40000000; // Set interrupt 19 priority to 2

    // NVIC enable
    *NVIC_EN0 |= 0x00080000;

    // Enable timer
    TIMER0->CTL |= 0x03; // bit 0 to enable and bit 1 to stall on debug
    return;
}

void TIMER0A_Handler(void)
{
    WaitGame = false;
    TIMER0->TAILR = 3200000 + (ReadPot() * 7033); //read value from poten and chnage game time
    TIMER0->ICR = 0x01; // clr interrupt
}
