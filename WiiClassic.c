#include "WiiClassic.h"

static uint8_t readReg(uint8_t ucAddr);
static uint16_t readReg16(uint8_t ucAddr);
static void writeReg16(uint8_t ucAddr, uint16_t usValue);
static void writeReg(uint8_t ucAddr, uint8_t ucValue);

//
// Read a pair of registers as a 16-bit value
//
static uint16_t readReg16(uint8_t ucAddr)
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
static uint8_t readReg(uint8_t ucAddr)
{
    uint8_t wbytes[] = { ucAddr };
    write_bytes(WII_I2C_ADDR, wbytes, 1);
    uint8_t *rbytes;
    read_bytes(WII_I2C_ADDR, rbytes, 1);
    return rbytes[0];
} 

static void readMulti(uint8_t ucAddr, uint8_t *pBuf, uint16_t iCount)
{
    uint8_t wbytes[] = { ucAddr };
    write_bytes(WII_I2C_ADDR, wbytes, 1);
    read_bytes(WII_I2C_ADDR, pBuf, iCount);
} 

static void writeMulti(uint8_t ucAddr, uint8_t *pBuf, uint16_t iCount)
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
static void writeReg16(uint8_t ucAddr, uint16_t usValue)
{
    uint8_t bytes[] = {ucAddr, usValue >> 8, usValue & 0xFF};
    
    write_bytes(WII_I2C_ADDR, bytes, 3);
} 

//
// Write a single register/value pair
//
static void writeReg(uint8_t ucAddr, uint8_t ucValue)
{
    uint8_t bytes[] = { ucAddr, ucValue & 0xFF };
    write_bytes(WII_I2C_ADDR, bytes, 2);
} 

//
// Write a list of register/value pairs to the I2C device
//
static void writeRegList(uint8_t *ucList, uint16_t no_pairs)
{
    uint16_t i;
    for (i = 0; i<no_pairs; i++) {
      writeReg(*ucList, *(ucList+1));
      ucList += 2;
    }
} 

void delay(uint32_t delay) {
    uint32_t i;
    for (i = 0; i<delay; i++);    
}

void init_WiiClassic() {
    // Initialise with unencrypted data communication
    set_clock_divider(CDIV_10kHz);
    writeReg(0xF0, 0x55);
    writeReg(0xFB, 0x00);
}

bool read_WiiClassic(uint8_t addr) {
    uint8_t err = 0;
    bool dataBad = true;
    uint16_t b;
    uint8_t readBytes = 0;
    for(b = 0; b<5; b++) {
        uint8_t byte[] = { addr }; 
        write_bytes(WII_I2C_ADDR, byte, 1);
        uint8_t* bytes;
        read_bytes(WII_I2C_ADDR, bytes, dataArraySize);     
    }
}





