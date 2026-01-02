#include "TM4C123GH6PM.h"


void Delay3(uint32_t n)
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
void InitPF4(void) {
    SYSCTL->RCGCGPIO |= 0x20; //Enable clock for PF
    // Wait for clock to stabilize
    __ASM("NOP"); 
    __ASM("NOP"); 
    __ASM("NOP");
    GPIOF->DIR &= ~0x10;      //Input
    GPIOF->PUR |= 0x10;       //Pull up resistor
    GPIOF->DEN |= 0x10;       //Digital
}

// Returns true ONLY if the button is solidly pressed
bool IsPF4PressedDebounced(void) {
    // 1. Check if button is pressed (Active Low)   
    if ((GPIOF->DATA & 0x10) == 0) {
        
        // 2. Wait ~20ms to let the bounce settle
        // Adjust this value if needed (approx 160000 cycles for Tiva @ 16MHz)
        Delay3(40000); 
        
        // 3. Check again. If it is still 0, it's a real press.
        if ((GPIOF->DATA & 0x10) == 0) {
            return true;
        }
    }
    return false;
}