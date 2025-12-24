#include "TM4C123GH6PM.h"
#include <stdint.h>

// Function Prototypes
void Delay(uint32_t n);
void SSI0_Init(void);
void ScreenInit(void);
void ScreenWrite(uint8_t type, uint8_t message);
void ScreenClear(void);

// SSI0_Init
// Configures SSI0 and GPIO Port A with MANUAL Chip Select
// PA2(Clk), PA3(CS), PA5(Tx), PA6(DC), PA7(RST) 
// ---------------------------------------------------------------------------
void SSI0_Init(void){

  // Start Clks
  SYSCTL->RCGCGPIO |= 0x01;   // Enable Clock for GPIO Port A
  while((SYSCTL->PRGPIO & 0x01) == 0){};   // Wait for GPIO Port A to be ready
  SYSCTL->RCGCSSI |= 0x01;  // Enable Clock for SSI0
  while((SYSCTL->PRSSI & 0x01) == 0){};  // Wait for SSI0 to be ready

  // GPIO A Config
  GPIOA->DEN |= 0xEC;   // Binary: 1110 1100 //PA2 PA3 PA5 PA6 PA7
  GPIOA->DIR |= 0xEC; // Binary: 1110 1100 //PA2 PA3 PA5 PA6 PA7
  GPIOA->AFSEL |= 0x24; // Binary: 0010 0100 //Enable for PA2 PA5
  GPIOA->AFSEL &= ~0xC8; // Disable for PA3 PA6 PA7
  // Set PMCx to 2 for PA2 and PA5. Clear others to 0.
  GPIOA->PCTL &= 0x00F0F0FF; // Clear nibbles for PA7,6,5,3,2
  GPIOA->PCTL |= 0x00200200; // Set nibbles for PA5 and PA2 to 2

  // SSI Configuration
  SSI0->CR1 &= ~0x02; // Disable SSI during configuration
  SSI0->CPSR = 50; // Clk Rate Using Divisor 50 to ensure we don't exceed Nokia's 4MHz limit
  SSI0->CR0 &= ~0x0000FF00;   // SCR = 0
  SSI0->CR0 &= ~0x000000C0;   // SPO=0, SPH=0
  SSI0->CR0 &= ~0x00000030;   // FRF = Freescale
  SSI0->CR0 = (SSI0->CR0 & ~0x0000000F) + 0x07; //Set Data Size to 8-bit
  SSI0->CR1 |= 0x02; //Enable SSI
  GPIOA->DATA |= 0x08; //Set CS (PA3) High (Idle state)
}

// ---------------------------------------------------------------------------
// Nokia5110 Screen Init
// ---------------------------------------------------------------------------
void ScreenInit(void){
  SSI0_Init();
  
  // Reset Pulse (Low -> Wait -> High)
  GPIOA->DATA &= ~0x80; // PA7 Low (RST)
  Delay(50000);               // Wait
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
// ---------------------------------------------------------------------------
void ScreenWrite(uint8_t type, uint8_t message){
  while((SSI0->SR & 0x02) == 0){}; //Wait until SSI is ready to transmit
  //Set to data or command
  if(type == 0){
    GPIOA->DATA &= ~0x40; // PA6 Low = Command
  } else {
    GPIOA->DATA |= 0x40;  // PA6 High = Data
  }
  GPIOA->DATA &= ~0x08; //Manual CS: Pull PA3 Low to start transmission
  SSI0->DR = message;
  while(SSI0->SR & 0x10){}; //Wait for transmission to complete (Busy Bit = 0)
  GPIOA->DATA |= 0x08; //Manual CS: Push PA3 High to end transmission
}

void Delay(uint32_t n){
  // 'volatile' tells the compiler "Do not delete this variable/loop"
  volatile uint32_t time; 
  while(n > 0){
    time = n; // Dummy operation
    n--;
  }
}

// Helper to clear screen
void ScreenClear(void){
    int i;
    ScreenWrite(0, 0x80); // X=0
    ScreenWrite(0, 0x40); // Y=0
    for(i=0; i<504; i++){
        ScreenWrite(1, 0x00);
    }
}
