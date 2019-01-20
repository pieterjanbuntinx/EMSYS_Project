#include "WiiClassic.h"

static void decode_WiiClassic();

//
// Read a pair of registers as a 16-bit value
//
uint16_t readReg16(uint8_t ucAddr)
{
    uint8_t wbytes[] = { ucAddr };
    write_bytes(WII_I2C_ADDR, wbytes, 1);
    uint8_t *rbytes;
    read_bytes(WII_I2C_ADDR, rbytes, 2);
    return ((rbytes[1])<<8) | (rbytes[0]);
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
    // Initialise to enable unencrypted data communication
    RPI_GetI2CController()->CLKT = CDIV_10kHz & 0xFFFF;
    writeReg(0xF0, 0x55);
    micros(1000);
    writeReg(0xFB, 0x00);
    micros(1000);
    wii_classic_update = true;
}

void read_WiiClassic(uint8_t addr) {
    uint8_t byte[] = { addr };

    write_bytes(WII_I2C_ADDR, byte, 1);
    micros(1000);
    read_bytes(WII_I2C_ADDR, data, dataArraySize);
    decode_WiiClassic();
}

int read_WiiClassic_int(uint8_t addr) {
    uint8_t byte[] = { addr };

    write_bytes_int(WII_I2C_ADDR, byte, 1);
    while(read_bytes_int(WII_I2C_ADDR, data, dataArraySize));
    decode_WiiClassic();
    return true;
}

static void decode_WiiClassic() {
    RX = ((data[0] & 0xC0) >> 3)  | ((data[1] & 0xC0) >> 5) | ((data[2] & 0x80) >> 7);
    RY = (data[2] & 0x1F);

    LX = (data[0] & 0x3F);
    LY = (data[1] & 0x3F);

    LT = ((data[2] >> 2) & 0x18) | ((data[1] >> 5) & 0x07);
    RT = (data[3] & 0x1F);

    uint8_t _DPAD[4] = {((data[5] & 0b10) >> 1), ((data[4] & 0x80) >> 7),  ((data[5] & 0b1) >> 0), ((data[4] & 0x40) >> 6)}; // BD{L,R,U,D}

    uint8_t _TRIGGER_CLICK[2] = {((data[4] & 0x20) >> 5), ((data[4] & 0b10) >> 1)}; // B{LT,RT}

    uint8_t _BUTTONS[9] = {((data[5] & 0b100) >> 2), ((data[5] & 0x80) >> 7), ((data[5] & 0x10) >> 4), ((data[5] & 0x40) >> 6), ((data[5] & 0x8) >> 3), ((data[5] & 0x20) >> 5), ((data[4] & 0x4) >> 2), ((data[4] & 0x8) >> 3), ((data[4] & 0x10) >> 4)}; // B{ZR,ZL,A,B,X,Y,+,H,-}   

    memcpy(DPAD, _DPAD, sizeof(_DPAD));
    memcpy(TRIGGER_CLICK, _TRIGGER_CLICK, sizeof(_TRIGGER_CLICK));
    memcpy(BUTTONS, _BUTTONS, sizeof(_BUTTONS));
}

void print_WiiClassic() {
    uprintf("RX: %d, RY: %d, LX: %d, LY: %d, LT: %d, RT: %d\n\rDPAD L: %d, R: %d, U: %d, D: %d, TRIGGER L: %d, R: %d\n\r", RX, RY, LX, LY, LT, RT, DPAD[0], DPAD[1], DPAD[2], DPAD[3], TRIGGER_CLICK[0], TRIGGER_CLICK[1]);
    micros(10*1000);
    uprintf("BUTTONS ZR: %d, ZL: %d, A: %d, B: %d, X: %d, Y: %d, +: %d, H: %d, -: %d\n\r", BUTTONS[0], BUTTONS[1], BUTTONS[2], BUTTONS[3], BUTTONS[4], BUTTONS[5], BUTTONS[6], BUTTONS[7], BUTTONS[8]);
}
