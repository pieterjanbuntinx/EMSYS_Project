#include "rpi-i2c.h"
#include "defines.h"
#include "rpi-uart.h"

rpi_i2c_controller_t *i2c_controller = (rpi_i2c_controller_t*) I2C_BASE;

rpi_i2c_controller_t* RPI_GetI2CController() {
    return i2c_controller;
}

/**
 * Data FIFO register
 */

uint8_t read_byte_from_FIFO() {
    return i2c_controller->FIFO & 0xFF;
}

void write_bytes_to_FIFO(uint8_t *bytes, uint16_t no_bytes) {
    //write 16 bytes or the number of bytes left to the fifo
    uint16_t i;
    for (i=0; (i<no_bytes) && (i<16); i++) {
        i2c_controller->FIFO = (*(bytes+i) & 0xFF);
    }
}

void reset_status_register() {
    i2c_controller->S = I2C_S_CLKT | I2C_S_ERR | I2C_S_DONE;
}

void clear_FIFO_data() {
    i2c_controller->C = I2C_C_CLEAR;
}

void read_bytes(uint8_t address, uint8_t *bytes, uint16_t no_bytes) {
    reset_status_register();
    clear_FIFO_data();

    i2c_controller->A = address & 0x7F;
    i2c_controller->DLEN = no_bytes & 0xFFFF;
    i2c_controller->C = START_READ;

    while (!(i2c_controller->S & I2C_S_DONE)) {
        // Check if the FIFO is full but not all the data has been transmitted
        if (i2c_controller->S & I2C_S_RXR) {
            uint16_t i;
            //read 16 bytes from the FIFO
            for (i=0; i<16; i++) {
                *bytes = read_byte_from_FIFO();
                bytes++;
                no_bytes--;
            }
        } 
        else if (i2c_controller->S & I2C_S_ERR) {
            //NACK received
            break;
        }
    }

    //read remaining data in the fifo
    uint16_t i;
    for (i=0; i<no_bytes; i++) {
        *bytes = read_byte_from_FIFO();
        bytes++;
    }
}

void write_bytes(uint8_t address, uint8_t *bytes, uint16_t no_bytes) {
    reset_status_register();
    clear_FIFO_data();

    i2c_controller->A = address & 0x7F;
    
    write_bytes_to_FIFO(bytes, no_bytes);    
    i2c_controller->DLEN = no_bytes & 0xFFFF;
    i2c_controller->C = START_WRITE; 

    while(!(i2c_controller->S & I2C_S_DONE)) {
        // check if the FIFO is empty but not all the data has been transmitted
        if (i2c_controller->S & I2C_S_TXW) {
            no_bytes -= 16;
            bytes += 16;
            write_bytes_to_FIFO(bytes, no_bytes);
        }
        else if (i2c_controller->S & I2C_S_ERR) {
            //NACK
            break;
        }
    }
}

volatile uint8_t *bytes_to_read_write;
volatile uint16_t no_bytes_left;
volatile bool busy;

int read_bytes_int(uint8_t address, uint8_t *bytes, uint16_t no_bytes) {
    if (busy) return false;

    busy = true;

    _lock();
    reset_status_register();
    clear_FIFO_data();

    i2c_controller->A = address & 0x7F;
    i2c_controller->DLEN = no_bytes & 0xFFFF;
    i2c_controller->C = START_READ;
    no_bytes_left = no_bytes;
    bytes_to_read_write = bytes;
    _unlock();
    return true;
}

int write_bytes_int(uint8_t address, uint8_t *bytes, uint16_t no_bytes) {
    if (busy) return false;
    busy = true;
    
    _lock();
    reset_status_register();
    clear_FIFO_data();

    write_bytes_to_FIFO(bytes, no_bytes);
    if (no_bytes > 16) {
        no_bytes_left = no_bytes - 16;   
        bytes_to_read_write = bytes;
    } else 
        no_bytes_left = 0;
    
    i2c_controller->DLEN = no_bytes & 0xFFFF;
    i2c_controller->C = START_WRITE;
    _unlock();
    return true;
}

void i2c_interrupt_handler() {
    if (i2c_controller->S & I2C_S_RXR) {
        uint16_t i;
        for (i=0; i<16; i++) {
            *bytes_to_read_write = read_byte_from_FIFO();
            bytes_to_read_write++;
            no_bytes_left--;
        }
    }

    if (i2c_controller->S & I2C_S_TXW) {
        no_bytes_left -= 16;
        bytes_to_read_write += 16;
        write_bytes_to_FIFO((uint8_t*)bytes_to_read_write, (uint16_t)no_bytes_left);
    }

    if (i2c_controller->S & I2C_S_DONE) {
        busy = false;

        //check if the finished operation was reading
        if (i2c_controller->S & I2C_C_READ) {
            //read the remaining bytes in the fifo
            uint16_t i;
            for (i=0; i<no_bytes_left; i++) {
                *bytes_to_read_write = read_byte_from_FIFO();
                bytes_to_read_write++;
            }
        }
    }

}

