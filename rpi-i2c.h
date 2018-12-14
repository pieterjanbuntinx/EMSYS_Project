#ifndef RPI_I2C_H
#define RPI_I2C_H

#include "defines.h"

struct bcm2835_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};

void wait_i2c_done();

void read_bytes(unsigned int , unsigned int *, unsigned int);
void write_bytes(unsigned int , unsigned int *, unsigned int);

int getAddress();

#endif
