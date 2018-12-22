#include "WiiClassic.h"

uint8_t RX;
uint8_t RY;
uint8_t LX;
uint8_t LY;
uint8_t LT;
uint8_t RT;
uint8_t DPAD[4];
uint8_t TRIGGER_CLICK[2];
uint8_t BUTTONS[9];

//
// Read a pair of registers as a 16-bit value
//
uint16_t readReg16(uint8_t ucAddr)
{
    uint8_t wbytes[] = { ucAddr };
    write_bytes(WII_I2C_ADDR, wbytes, 1);
    uint8_t *rbytes;
    read_bytes(WII_I2C_ADDR, rbytes, 2);
    return (rbytes[1]) | (rbytes[0]);
} 

//
// Read a single register value from I2C device
//
uint8_t readReg(uint8_t ucAddr)
{
    uint8_t wbytes[] = { ucAddr };
    write_bytes(WII_I2C_ADDR, wbytes, 1);
    uint8_t *rbytes;
    read_bytes(WII_I2C_ADDR, rbytes, 1);
    return rbytes[0];
} 

void readMulti(uint8_t ucAddr, uint8_t *pBuf, uint16_t iCount)
{
    uint8_t wbytes[] = { ucAddr };
    write_bytes(WII_I2C_ADDR, wbytes, 1);
    read_bytes(WII_I2C_ADDR, pBuf, iCount);
} 

void writeMulti(uint8_t ucAddr, uint8_t *pBuf, uint16_t iCount)
{
    uint8_t *bytes;
    bytes[0] = ucAddr;
    uint16_t i;
    for (i = 0; i<iCount; i++) {
        bytes[i+1] = pBuf[i];
    }
    write_bytes(WII_I2C_ADDR, bytes, iCount+1);
} /* writeMulti() */

//
// Write a 16-bit value to a register
//
void writeReg16(uint8_t ucAddr, uint16_t usValue)
{
    uint8_t bytes[] = {ucAddr, usValue >> 8, usValue & 0xFF};
    
    write_bytes(WII_I2C_ADDR, bytes, 3);
} 

//
// Write a single register/value pair
//
void writeReg(uint8_t ucAddr, uint8_t ucValue)
{
    uint8_t bytes[] = { ucAddr, ucValue & 0xFF };
    write_bytes(WII_I2C_ADDR, bytes, 2);
} 

//
// Write a list of register/value pairs to the I2C device
//
void writeRegList(uint8_t *ucList, uint16_t no_pairs)
{
    uint16_t i;
    for (i = 0; i<no_pairs; i++) {
      writeReg(*ucList, *(ucList+1));
      ucList += 2;
    }
} 

void init_WiiClassic() {
    // Initialise with unencrypted data communication
    set_clock_divider(CDIV_10kHz);
    writeReg(0xF0, 0x55);
    writeReg(0xFB, 0x00);
    micros(100*1000);
}

void read_WiiClassic(uint8_t addr) {
    uint8_t byte[] = { addr };
    uint8_t *bytes;

    write_bytes(WII_I2C_ADDR, byte, 1);
    micros(100*1000);
    read_bytes(WII_I2C_ADDR, bytes, dataArraySize);

    RX = ((bytes[0] & 0xC0) >> 3)  | ((bytes[1] & 0xC0) >> 5) | ((bytes[2] & 0x80) >> 7);
    RY = (bytes[2] & 0x1F);

    LX = (bytes[0] & 0x3F);
    LY = (bytes[1] & 0x3F);

    LT = ((bytes[2] >> 2) & 0x18) | ((bytes[1] >> 5) & 0x07);
    RT = (bytes[3] & 0x1F);

    const uint8_t _DPAD[4] = {((bytes[5] & 0b10) >> 1), ((bytes[4] & 0x80) >> 7),  ((bytes[5] & 0b1) >> 0), ((bytes[4] & 0x40) >> 6)}; // BD{L,R,U,D}

    const uint8_t _TRIGGER_CLICK[2] = {((bytes[4] & 0x20) >> 5), ((bytes[4] & 0b10) >> 1)}; // B{LT,RT}

    const uint8_t _BUTTONS[9] = {((bytes[5] & 0b100) >> 2), ((bytes[5] & 0x80) >> 7), ((bytes[5] & 0x10) >> 4), ((bytes[5] & 0x40) >> 6), ((bytes[5] & 0x8) >> 3), ((bytes[5] & 0x20) >> 5), ((bytes[4] & 0x4) >> 2), ((bytes[4] & 0x8) >> 3), ((bytes[4] & 0x10) >> 4)}; // B{ZR,ZL,A,B,X,Y,+,H,-}   

    memcpy(DPAD, _DPAD, sizeof(_DPAD));
    memcpy(TRIGGER_CLICK, _TRIGGER_CLICK, sizeof(_TRIGGER_CLICK));
    memcpy(BUTTONS, _BUTTONS, sizeof(_BUTTONS));
}

void print_WiiClassic() {
    uprintf("RX: %d, RY: %d, LX: %d, LY: %d, LT: %d, RT: %d, DPAD L: %d, R: %d, U: %d, D: %d, TRIGGER L: %d, R: %d \n\r", RX, RY, LX, LY, LT, RT, DPAD[0], DPAD[1], DPAD[2], DPAD[3], TRIGGER_CLICK[0], TRIGGER_CLICK[1]);
    micros(100*1000);
    uprintf("BUTTONS ZR: %d, ZL: %d, A: %d, B: %d, X: %d, Y: %d, +: %d, H: %d, -: %d\n\r", BUTTONS[0], BUTTONS[1], BUTTONS[2], BUTTONS[3], BUTTONS[4], BUTTONS[5], BUTTONS[6], BUTTONS[7], BUTTONS[8]);
}
