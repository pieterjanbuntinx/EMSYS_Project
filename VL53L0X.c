#include "VL53L0X.h"
#include "rpi-uart.h"

#define ADDRESS_DEFAULT 0b0101001

// write 8 bit register
void writeReg(int reg, int value) {
    int bytes[] = { reg, value };
    write_bytes(ADDRESS_DEFAULT, bytes, 2);
}

int readReg(int reg) {
    int wbytes[] = { reg };
    write_bytes(ADDRESS_DEFAULT, wbytes, 1);
    int *rbytes;
    read_bytes(ADDRESS_DEFAULT, rbytes, 1);
    return rbytes[0];
}


int init_device() {
    // "Set I2C standard mode"
    writeReg(0x88, 0x00);

    writeReg(0x80, 0x01);
    writeReg(0xFF, 0x01);
    writeReg(0x00, 0x00);
    stop_variable = readReg(0x91);
    uprintf("stop_var=%d", stop_variable);
    writeReg(0x00, 0x01);
    writeReg(0xFF, 0x00);
    writeReg(0x80, 0x00);
}

