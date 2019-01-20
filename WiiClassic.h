#ifndef WIICLASSIC_H
#define WIICLASSIC_H

#include "rpi-uart.h"
#include "rpi-i2c.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "defines.h"
#include "rpi-armtimer.h"
#include <string.h>

#define WII_I2C_ADDR	0x52
#define CDIV_10kHz 15000

#define WII_BYTE0 0
#define WII_BYTE1 1
#define WII_BYTE2 2
#define WII_BYTE3 3
#define WII_BYTE4 4
#define WII_BYTE5 5
#define WII_UNUSED 255

#define WII_BIT0 0
#define WII_BIT1 1
#define WII_BIT2 2
#define WII_BIT3 3
#define WII_BIT4 4
#define WII_BIT5 5
#define WII_BIT6 6
#define WII_BIT7 7

#define WII_VALUES_ARRAY_SIZE 19
#define dataArraySize 6

#define joyXLeftBytes	    WII_UNUSED,     0,     0,   WII_UNUSED,        0,     0, WII_BYTE0,  WII_BIT0, WII_BIT5
#define joyXRightBytes	    WII_BYTE0,   WII_BIT6,  WII_BIT7,    WII_BYTE1,     WII_BIT6,  WII_BIT7, WII_BYTE2,  WII_BIT7, WII_BIT7
#define joyYLeftBytes	    WII_UNUSED,     0,     0,   WII_UNUSED,        0,     0, WII_BYTE1,  WII_BIT0, WII_BIT5
#define joyYRightBytes	    WII_UNUSED,     0,     0,   WII_UNUSED,        0,     0, WII_BYTE2,  WII_BIT0, WII_BIT4

#define triggerLeftBytes	WII_UNUSED,     0,     0,    WII_BYTE2,     WII_BIT5,  WII_BIT6, WII_BYTE3,  WII_BIT5, WII_BIT7
#define triggerRightBytes	WII_UNUSED,     0,     0,   WII_UNUSED,        0,     0, WII_BYTE3,  WII_BIT0, WII_BIT4

#define padRightBytes	    WII_BYTE4,WII_BIT7,true
#define padDownBytes	    WII_BYTE4,WII_BIT6,true
#define padUpBytes	        WII_BYTE5,WII_BIT0,true
#define padLeftBytes	    WII_BYTE5,WII_BIT1,true

#define buttonXBytes	    WII_BYTE5,WII_BIT3,true
#define buttonYBytes	    WII_BYTE5,WII_BIT5,true
#define buttonABytes	    WII_BYTE5,WII_BIT4,true
#define buttonBBytes	    WII_BYTE5,WII_BIT6,true

#define buttonMinusBytes    WII_BYTE4,WII_BIT4,true
#define buttonHomeBytes	    WII_BYTE4,WII_BIT3,true
#define buttonPlusBytes	    WII_BYTE4,WII_BIT2,true

#define buttonZRBytes	    WII_BYTE5,WII_BIT2,true
#define buttonZLBytes	    WII_BYTE5,WII_BIT7,true

bool wii_classic_update;
uint8_t RX;
uint8_t RY;
uint8_t LX;
uint8_t LY;
uint8_t LT;
uint8_t RT;
uint8_t DPAD[4];
uint8_t TRIGGER_CLICK[2];
uint8_t BUTTONS[9];

uint8_t data[6];

uint8_t readReg(uint8_t ucAddr);
uint16_t readReg16(uint8_t ucAddr);
void writeReg16(uint8_t ucAddr, uint16_t usValue);
void writeReg(uint8_t ucAddr, uint8_t ucValue);
void readMulti(uint8_t ucAddr, uint8_t *pBuf, uint16_t iCount);
void writeMulti(uint8_t ucAddr, uint8_t *pBuf, uint16_t iCount);

void init_WiiClassic();
void read_WiiClassic(uint8_t addr);
int read_WiiClassic_int(uint8_t addr);
void print_WiiClassic();

#endif
