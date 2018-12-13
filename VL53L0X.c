#include "VL53L0X.h"

#define ADDRESS_DEFAULT 0b0101001

void writeReg(int reg, int *value) {
    write_bytes(ADDRESS_DEFAULT, value, 1);
}

void readReg(int reg, int *data) {
    
}

int init_device() {
    // "Set I2C standard mode"
    writeReg(0x88, 0x00);

    writeReg(0x80, 0x01);
    writeReg(0xFF, 0x01);
    writeReg(0x00, 0x00);
}

