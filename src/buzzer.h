#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "stdbool.h"
#include "Utils.h"

void InitBuzzer(void);
void MakeSound(int freq, int duration_ms);
void MakeGoodMelody();
void MakeBadMelody();
void TIMER2A_Handler(void); // Handles Frequency (Sound Generation)
void TIMER3A_Handler(void); // Handles Duration (Stops Sound)

SoundNote MelodyArray[10];
int MelodyLength;

void InitBuzzer(void)
{
    MelodyLength = 0;
    // --- 1. Define NVIC Pointers ---
    volatile int *NVIC_EN0 = (volatile int *)0xE000E100;
    volatile int *NVIC_PRI5 = (volatile int *)0xE000E414;
    volatile int *NVIC_EN1 = (volatile int *)0xE000E104;
    volatile int *NVIC_PRI8 = (volatile int *)0xE000E420;

    // --- 2. Clock Setup ---
    SYSCTL->RCGCGPIO |= 0x20;
    SYSCTL->RCGCTIMER |= 0x0C; // Enable Timer 2 and Timer 3
    __ASM("NOP");
    __ASM("NOP");
    __ASM("NOP");

    // --- 3. GPIO Setup (PF3) ---
    GPIOF->DIR |= 0x08;
    GPIOF->AFSEL &= ~0x08;
    GPIOF->PCTL &= ~0x0000F000;
    GPIOF->AMSEL &= ~0x08;
    GPIOF->DEN |= 0x08;

    // --- 4. Timer 2 Setup (Sound Freq - 16-bit Mode) ---
    TIMER2->CTL &= ~0x01;
    TIMER2->CFG = 0x04;  // 16-bit mode
    TIMER2->TAMR = 0x02; // Periodic
    TIMER2->TAPR = 15;   // Prescaler 15 -> 1MHz Clock (OK because 15 < 255)
    TIMER2->TAILR = 1000;
    TIMER2->IMR |= 0x01;

    // --- 5. Timer 3 Setup (Duration - 32-bit Mode) ---
    TIMER3->CTL &= ~0x01;
    TIMER3->CFG = 0x00;  // <--- 32-bit mode (Combines A and B)
    TIMER3->TAMR = 0x01; // One-Shot mode
    TIMER3->TAPR = 0;    // No prescaler needed for 32-bit
    TIMER3->IMR |= 0x01; // Enable Interrupt on Timeout

    // --- 6. NVIC Setup ---

    // Timer 2A (Int 23) -> Priority 2
    *NVIC_PRI5 &= 0x00FFFFFF;
    *NVIC_PRI5 |= 0x40000000;
    *NVIC_EN0 |= 0x00800000;

    // Timer 3A (Int 35) -> Priority 2
    // Note: In 32-bit mode, Timer 3A interrupt handles the whole 32-bit timer.
    *NVIC_PRI8 &= 0x00FFFFFF;
    *NVIC_PRI8 |= 0x40000000;
    *NVIC_EN1 |= 0x00000008;
}
void MakeSound(int freq, int duration_ms)
{
    // 1. Setup the Sound (Timer 2)
    if (freq > 0)
    {
        // Calculate Half-Period in microseconds
        // Formula: (1MHz Clock / Frequency) / 2
        TIMER2->TAILR = (1000000 / freq) / 2;
        TIMER2->CTL |= 0x01;
    }
    else
    {
        TIMER2->CTL &= ~0x01; // Silence
    }

    // 2. Setup the Duration (Timer 3)
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
void MakeBadMelody()
{
    MelodyArray[0].duration = 500;
    MelodyArray[1].duration = 60; //
    MelodyArray[2].duration = 300;
    MelodyArray[3].duration = 60; //
    MelodyArray[4].duration = 300;
    MelodyArray[5].duration = 60; //
    MelodyArray[0].pitch = 247;
    MelodyArray[1].pitch = 0; //
    MelodyArray[2].pitch = 261;
    MelodyArray[3].pitch = 0; //
    MelodyArray[4].pitch = 277;
    MelodyArray[5].pitch = 0; //
    MelodyLength = 6;
    MakeSound(293, 300);
}

// Handler for Frequency
void TIMER2A_Handler(void)
{
    TIMER2->ICR = 0x01;
    GPIOF->DATA ^= 0x08;
}

// Handler for Duration (Timer 3)
void TIMER3A_Handler(void)
{
    TIMER3->ICR = 0x01; // Clear interrupt
    if (MelodyLength > 0)
    {
        MakeSound(MelodyArray[MelodyLength - 1].pitch, MelodyArray[MelodyLength - 1].duration);
        MelodyLength--;
    }
    else
    {
        // Stop the Sound
        TIMER2->CTL &= ~0x01; // Disable Timer 2
        GPIOF->DATA &= ~0x08; // Silence
    }
}