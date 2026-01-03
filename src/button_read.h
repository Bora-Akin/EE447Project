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
void InitPF4(void)
{
  SYSCTL->RCGCGPIO |= 0x20; // Enable clock for PF
  // Wait for clock to stabilize
  __ASM("NOP");
  __ASM("NOP");
  __ASM("NOP");
  GPIOF->DIR &= ~0x10; // Input
  GPIOF->PUR |= 0x10;  // Pull up resistor
  GPIOF->DEN |= 0x10;  // Digital
}

// Returns true when button is pressed
bool IsPF4PressedDebounced(void)
{
  // Active Low
  if ((GPIOF->DATA & 0x10) == 0)
  {
    Delay3(40000); // Delay for debounce
    // Check again
    if ((GPIOF->DATA & 0x10) == 0)
    {
      return true;
    }
  }
  return false;
}
// Returns true when button is released
bool IsPF4ReleasedDebounced(void)
{
  // Active Low
  if ((GPIOF->DATA & 0x10) != 0)
  {
    Delay3(40000); // Delay for debounce
    // Check again
    if ((GPIOF->DATA & 0x10) != 0)
    {
      return true;
    }
  }
  return false;
}