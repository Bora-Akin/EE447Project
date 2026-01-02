#include <stdint.h>
#include <stdlib.h>
#include "TM4C123GH6PM.h" // The file you provided

// ADXL345 Addresses
#define ADXL345_ADDRESS     0x53
#define ADXL_POWER_CTL      0x2D
#define ADXL_DATA_FORMAT    0x31
#define ADXL_DATAX0         0x32

// I2C Master Command Defines (Not usually in the struct header, so we define them)
#define I2C_MCS_STOP        0x00000004
#define I2C_MCS_START       0x00000002
#define I2C_MCS_RUN         0x00000001
#define I2C_MCS_ACK         0x00000008
#define I2C_MCS_DATACK      0x00000010

void I2C0_Init(void);
void I2C_Wait(void);
void ADXL_WriteOneByte(uint8_t reg, uint8_t data);
void ADXL345_Init(void);
void ADXL345_ReadXY(int16_t* x, int16_t* y);
int RawAccDataConverter(int xdat,int ydat, int curdir);

int InputDirection(int curDir){
    int16_t x;
    int16_t y;
    ADXL345_ReadXY(&x, &y);
    return RawAccDataConverter(x, y, curDir);
}

// ----------------------------------------------------------------------------
// Initialization of I2C0 on PB2 (SCL) and PB3 (SDA)
// ----------------------------------------------------------------------------
void I2C0_Init(void) {
    // 1. Enable Clock for I2C0 and GPIOB
    // Accessing SYSCTL registers via the SYSCTL pointer defined in your header
    SYSCTL->RCGCI2C |= 0x01;           // Enable I2C0 clock
    SYSCTL->RCGCGPIO |= 0x02;          // Enable Port B clock
    
    // Wait for Peripheral Ready (using the PRGPIO register in SYSCTL struct)
    while((SYSCTL->PRGPIO & 0x02) == 0){}; 

    // 2. Configure GPIO Pins (PB2, PB3)
    // Accessing GPIOB registers via the GPIOB pointer
    GPIOB->AFSEL |= 0x0C;         // Enable Alternate Function on PB2, PB3
    GPIOB->ODR   |= 0x08;         // Enable Open Drain on PB3 (SDA)
    GPIOB->DEN   |= 0x0C;         // Enable Digital I/O on PB2, PB3
    
    // Configure PCTL. Note: We must mask and set carefully.
    // 0x00003300 means nibble 2 and 3 are set to '3' (I2C function)
    GPIOB->PCTL = (GPIOB->PCTL & 0xFFFF00FF) | 0x00003300;

    // 3. Configure I2C0 Master
    I2C0->MCR = 0x00000010;       // Initialize I2C Master function
    
    // Set SCL Clock Speed to 100kHz (assuming 16MHz system clock)
    // TPR = (16MHz / (2 * (10) * 100000)) - 1 = 7
    I2C0->MTPR = 0x07;                 
}

// ----------------------------------------------------------------------------
// Low Level I2C Wait Function
// ----------------------------------------------------------------------------
void I2C_Wait(void) {
    // Wait while I2C Master is busy (Bit 0 of MCS)
    while((I2C0->MCS & 0x00000001) != 0) {}; 
}

// ----------------------------------------------------------------------------
// Write One Byte to ADXL345
// ----------------------------------------------------------------------------
void ADXL_WriteOneByte(uint8_t reg, uint8_t data) {
    // 1. Set Slave Address (0 = Write)
    I2C0->MSA = (ADXL345_ADDRESS << 1) & 0xFE; 
    
    // 2. Send Register Address
    I2C0->MDR = reg;
    I2C0->MCS = (I2C_MCS_START | I2C_MCS_RUN); 
    I2C_Wait();

    // 3. Send Data
    I2C0->MDR = data;
    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_STOP); 
    I2C_Wait();
}

// ----------------------------------------------------------------------------
// Initialize ADXL345 (Set Range and Measurement Mode)
// ----------------------------------------------------------------------------
void ADXL345_Init(void) {
    I2C0_Init();
    
    // Set Measurement Bit
    ADXL_WriteOneByte(ADXL_POWER_CTL, 0x08);

    // Set Full Resolution, +/- 4g
    ADXL_WriteOneByte(ADXL_DATA_FORMAT, 0x09);
}

// ----------------------------------------------------------------------------
// Read X and Y Data
// ----------------------------------------------------------------------------
void ADXL345_ReadXY(int16_t* x, int16_t* y) {
    // 1. Set Address to X0 Register (Write Mode)
    I2C0->MSA = (ADXL345_ADDRESS << 1) & 0xFE; 
    I2C0->MDR = ADXL_DATAX0;                   
    I2C0->MCS = (I2C_MCS_START | I2C_MCS_RUN); 
    I2C_Wait();

    // 2. Switch to Read Mode
    I2C0->MSA = (ADXL345_ADDRESS << 1) | 0x01; 
    
    // Read Byte 1: X0 (ACK)
    I2C0->MCS = (I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_ACK);
    I2C_Wait();
    uint8_t x0 = I2C0->MDR;

    // Read Byte 2: X1 (ACK)
    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_ACK);
    I2C_Wait();
    uint8_t x1 = I2C0->MDR;

    // Read Byte 3: Y0 (ACK)
    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_ACK);
    I2C_Wait();
    uint8_t y0 = I2C0->MDR;

    // Read Byte 4: Y1 (STOP, No ACK)
    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_STOP);
    I2C_Wait();
    uint8_t y1 = I2C0->MDR;

    // Combine
    *x = (int16_t)((x1 << 8) | x0);
    *y = (int16_t)((y1 << 8) | y0);
}

int RawAccDataConverter(int xdat,int ydat, int curdir){
	int nextdir;
	int absX = abs(xdat);
	int absY = abs(ydat);
	if ((absX < 128) && (absY < 128)){ //deadzone 
			nextdir = curdir;
	}
	else if (absX >= absY){
		if (xdat > 0){
			nextdir = 1;
		}
		else {
			nextdir = 3;
		}
	}
	else {
		if (ydat > 0){
			nextdir = 2;
		}
		else {
			nextdir = 0;
		}
	}
	return nextdir;
}