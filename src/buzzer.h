#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "stdbool.h"
#include "Utils.h"

void InitBuzzer(void);
void MakeSound(int freq, int duration_ms);
void MakeGoodMelody();
void MakeBadMelody();
void MakeAppleMelody();
void TIMER2A_Handler(void); // Determinies sound Freq
void TIMER3A_Handler(void); // DEtermines sound duration

SoundNote MelodyArray[10];
int MelodyLength;

void InitBuzzer(void)
{
    MelodyLength = 0;
    volatile int *NVIC_EN0 = (volatile int *)0xE000E100;
    volatile int *NVIC_PRI5 = (volatile int *)0xE000E414;
    volatile int *NVIC_EN1 = (volatile int *)0xE000E104;
    volatile int *NVIC_PRI8 = (volatile int *)0xE000E420;

    // CLK initialize
    SYSCTL->RCGCGPIO |= 0x10;  // GPIO E
    SYSCTL->RCGCTIMER |= 0x0C; // Enable Timer 2 and Timer 3
    __ASM("NOP");
    __ASM("NOP");
    __ASM("NOP");

    // PE4
    GPIOE->DIR |= 0x10;
    GPIOE->AFSEL &= ~0x10;
    GPIOE->PCTL &= ~0x000F0000;
    GPIOE->AMSEL &= ~0x10;
    GPIOE->DEN |= 0x10;

    // TIMER 2, Sound Freq
    TIMER2->CTL &= ~0x01;
    TIMER2->CFG = 0x04;  // 16 bit mode
    TIMER2->TAMR = 0x02; // Periodic
    TIMER2->TAPR = 15;   // 1MHz Clk
    TIMER2->TAILR = 1000;
    TIMER2->IMR |= 0x01; // Enable Interrupt on Timeout

    // TIMER 3, sound duration
    TIMER3->CTL &= ~0x01;
    TIMER3->CFG = 0x00;  // 32 bit mode
    TIMER3->TAMR = 0x01; // One shot mode
    TIMER3->TAPR = 0;    // No prescaler
    TIMER3->IMR |= 0x01; // Enable Interrupt on Timeout

    // Timer 2A Priority 2
    *NVIC_PRI5 &= 0x00FFFFFF;
    *NVIC_PRI5 |= 0x40000000;
    *NVIC_EN0 |= 0x00800000;

    // Timer 3A Priority 2
    *NVIC_PRI8 &= 0x00FFFFFF;
    *NVIC_PRI8 |= 0x40000000;
    *NVIC_EN1 |= 0x00000008;
}
void MakeSound(int freq, int duration_ms)
{
    // Timer 2 setup sound freq
    if (freq > 0)
    {
        TIMER2->TAILR = (1000000 / freq) / 2;
        TIMER2->CTL |= 0x01;
    }
    else
    {
        TIMER2->CTL &= ~0x01; // Silence
    }
    // Timer 3 setup sound duration
    if (duration_ms > 0)
    {
        TIMER3->TAILR = duration_ms * 16000;
        TIMER3->CTL |= 0x01; // Start Timer 3
    }
}
void MakeGoodMelody()
{
    MelodyArray[0].duration = 500;
    MelodyArray[1].duration = 200;
    MelodyArray[2].duration = 200;
    MelodyArray[0].pitch = 440;
    MelodyArray[1].pitch = 369;
    MelodyArray[2].pitch = 440;
    MelodyLength = 3;
    MakeSound(293, 200);
}
void MakeAppleMelody()
{
    MelodyArray[0].duration = 200;
    MelodyArray[0].pitch = 880;
    MelodyLength = 1;
    MakeSound(440, 100);
}
void MakeBadMelody()
{
    MelodyArray[0].duration = 500;
    MelodyArray[1].duration = 60;
    MelodyArray[2].duration = 300;
    MelodyArray[3].duration = 60;
    MelodyArray[4].duration = 300;
    MelodyArray[5].duration = 60;
    MelodyArray[0].pitch = 247;
    MelodyArray[1].pitch = 0;
    MelodyArray[2].pitch = 261;
    MelodyArray[3].pitch = 0;
    MelodyArray[4].pitch = 277;
    MelodyArray[5].pitch = 0;
    MelodyLength = 6;
    MakeSound(293, 300);
}

// Handler for Frequency
void TIMER2A_Handler(void)
{
    TIMER2->ICR = 0x01;
    GPIOE->DATA ^= 0x10;
}

// Handler for Duration
void TIMER3A_Handler(void)
{
    TIMER3->ICR = 0x01; // Clear interrupt
    //If there is a next note in melody play the next sound
    if (MelodyLength > 0)
    {
        MakeSound(MelodyArray[MelodyLength - 1].pitch, MelodyArray[MelodyLength - 1].duration);
        MelodyLength--;
    }
    else
    {
        // Stop the Sound
        TIMER2->CTL &= ~0x01; // Disable Timer 2
        GPIOE->DATA &= ~0x10; // Silence
    }
}