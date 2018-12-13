#include "VL53L0X.h"

#define ADDRESS_DEFAULT 0b0101001

// write 8 bit register
void writeReg(int reg, int value) {
    int bytes[] = { reg, value };
    write_bytes(ADDRESS_DEFAULT, bytes, 2);
}

// read 8 bit register
int readReg(int reg) {
    int write_bytes[] = { reg };
    write_bytes(ADDRESS_DEFAULT, write_bytes, 1);
    int *read_bytes;
    read_bytes(ADDRESS_DEFAULT, read_bytes, 1);
    return read_bytes[1];
}

int init_device() {
    // "Set I2C standard mode"
    writeReg(0x88, 0x00);

    writeReg(0x80, 0x01);
    writeReg(0xFF, 0x01);
    writeReg(0x00, 0x00);
    stop_variable = readReg(0x91);
    writeReg(0x00, 0x01);
    writeReg(0xFF, 0x00);
    writeReg(0x80, 0x00);
}

