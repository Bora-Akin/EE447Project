#include <stdint.h>
#include <stdlib.h>
#include "TM4C123GH6PM.h"

#define ADXL345_ADDRESS 0x53  // address
#define ADXL_POWER_CTL 0x2D   // address for power control register
#define ADXL_DATA_FORMAT 0x31 // address for data format register
#define ADXL_DATAX0 0x32      // address for register LSB of X data

#define I2C_MCS_STOP 0x00000004  // I2C master sends a stop
#define I2C_MCS_START 0x00000002 // I2C master sends a start
#define I2C_MCS_RUN 0x00000001   // Run command
#define I2C_MCS_ACK 0x00000008   // sends ack

void I2C0_Init(void);
void I2C_Wait(void);
void ADXL_WriteOneByte(uint8_t reg, uint8_t data);
void ADXL345_Init(void);
void ADXL345_ReadXY(int16_t *x, int16_t *y);
int RawAccDataConverter(int xdat, int ydat, int curdir);

int InputDirection(int curDir)
{ // combines functions for easy call on main
    int16_t x;
    int16_t y;
    ADXL345_ReadXY(&x, &y);
    return RawAccDataConverter(x, y, curDir);
}

void I2C0_Init(void)
{
    SYSCTL->RCGCI2C |= 0x01;  // enable i2c0 clock
    SYSCTL->RCGCGPIO |= 0x02; // enable pb clock

    while ((SYSCTL->PRGPIO & 0x02) == 0)
    {
    }; // wait for clock to stabilize

    // pb2&3
    GPIOB->AFSEL |= 0x0C; // alternate function for pb2&3
    GPIOB->ODR |= 0x08;   // open drain for SDA (pb3)
    GPIOB->DEN |= 0x0C;   // enable digital i/o for pb2&3

    GPIOB->PCTL = (GPIOB->PCTL & 0xFFFF00FF) | 0x00003300; // configure pctl

    I2C0->MCR = 0x00000010; // initialize i2c master function

    // TPR = (sys_clk/(hardwarefixedcons*(scl_lp+scl_hp)*targetspeed))-1
    // TPR = (16MHz/(2*10*100000))-1 = 7
    I2C0->MTPR = 0x07;
}

void I2C_Wait(void)
{
    while ((I2C0->MCS & 0x00000001) != 0)
    {
    }; // waiting for response
}

void ADXL_WriteOneByte(uint8_t reg, uint8_t data)
{                                              // write one byte (while we initialize, we have to configure the adxl)
    I2C0->MSA = (ADXL345_ADDRESS << 1) & 0xFE; // slave address is 0x53 & 0xFE to 0 the last bit (its write bit)

    I2C0->MDR = reg;                           // register address
    I2C0->MCS = (I2C_MCS_START | I2C_MCS_RUN); // sends the register
    I2C_Wait();

    I2C0->MDR = data;                         // the data
    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_STOP); // sends the data
    I2C_Wait();
}

void ADXL345_Init(void)
{
    I2C0_Init();

    ADXL_WriteOneByte(ADXL_POWER_CTL, 0x08); // sets measure mode

    ADXL_WriteOneByte(ADXL_DATA_FORMAT, 0x09); // sets the resolution to +- 4g
}

void ADXL345_ReadXY(int16_t *x, int16_t *y)
{

    I2C0->MSA = (ADXL345_ADDRESS << 1) & 0xFE; // sends the address
    I2C0->MDR = ADXL_DATAX0;
    I2C0->MCS = (I2C_MCS_START | I2C_MCS_RUN);
    I2C_Wait();

    I2C0->MSA = (ADXL345_ADDRESS << 1) | 0x01; // starts to read

    I2C0->MCS = (I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_ACK);
    I2C_Wait();
    uint8_t x0 = I2C0->MDR; // byte 1 of x

    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_ACK);
    I2C_Wait();
    uint8_t x1 = I2C0->MDR; // byte 2 of x

    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_ACK);
    I2C_Wait();
    uint8_t y0 = I2C0->MDR; // byte 1 of y

    I2C0->MCS = (I2C_MCS_RUN | I2C_MCS_STOP);
    I2C_Wait();
    uint8_t y1 = I2C0->MDR; // byte 2 of y (does NOT send ack so slave stops to sends data of z)

    *x = (int16_t)((x1 << 8) | x0); // combines byte 1&2 of x
    *y = (int16_t)((y1 << 8) | y0); // combines byte 1&2 of y
}

int RawAccDataConverter(int xdat, int ydat, int curdir)
{ // direction values are according to the placement of the adxl on the breadboard
    int nextdir;
    int absX = abs(xdat);
    int absY = abs(ydat);
    if ((absX < 128) && (absY < 128))
    { // deadzone
        nextdir = curdir;
    }
    else if (absX >= absY)
    {
        if (xdat > 0)
        {
            nextdir = 1; // to right
        }
        else
        {
            nextdir = 3; // to left
        }
    }
    else
    {
        if (ydat > 0)
        {
            nextdir = 2; // to down
        }
        else
        {
            nextdir = 0; // to up
        }
    }
    return nextdir;
}