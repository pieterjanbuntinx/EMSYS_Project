#include "rpi-i2c.h"
#include "defines.h"
#include "rpi-uart.h"

/**
 * Control register
*/

void i2c_init() {
    i2c_reg = (unsigned int*) I2C_BASE;
}

void i2c_enable() {
    i2c_reg[I2C_CONTROL] |= (1 << 15);
}

void i2c_disable() {
    i2c_reg[I2C_CONTROL] &= ~(1 << 15);
}

void enable_int_RX() {
    i2c_reg[I2C_CONTROL] |= (1 << 10);
}

void disable_int_RX() {
    i2c_reg[I2C_CONTROL] &= ~(1 << 10);
}

void enable_int_TX() {
    i2c_reg[I2C_CONTROL] |= (1 << 9);
}

void disable_int_TX() {
    i2c_reg[I2C_CONTROL] &= ~(1 << 9);
}

void enable_int_DONE() {
    i2c_reg[I2C_CONTROL] |= (1 << 8);
}

void start_transfer() {
    i2c_enable();
    i2c_reg[I2C_CONTROL] |= (1 << 7);
}

void clear_FIFO_data() {
    i2c_reg[I2C_CONTROL] |= (1 << 4);
}

void set_read_transfer() {
    i2c_reg[I2C_CONTROL] |= (1 << 0);
}

void set_write_transfer() {
    i2c_reg[I2C_CONTROL] &= ~(1 << 0);
}

/**
 * Status register
*/

bool is_CLKT() {
    return (i2c_reg[I2C_STATUS] >> 9) & 1;
}

void reset_CLKT() {
    i2c_reg[I2C_STATUS] |= (1 << 9);
}

bool is_ERR() {
    return (i2c_reg[I2C_STATUS] & I2C_S_ERR);
}

void reset_ERR() {
    i2c_reg[I2C_STATUS] |= (1 << 8);
}

bool is_RX_FIFO_full() {
    return (i2c_reg[I2C_STATUS] >> 7) & 1;
}

bool is_TX_FIFO_empty() {
    return (i2c_reg[I2C_STATUS] >> 6) & 1;
}

bool does_RX_contain_DATA() {
    return (i2c_reg[I2C_STATUS] >> 5) & 1;
}

bool does_TX_accept_DATA() {
    return (i2c_reg[I2C_STATUS] >> 4) & 1;
}

bool does_RX_need_reading() {
    return (i2c_reg[I2C_STATUS] >> 3) & 1;
}

bool does_TX_need_writing() {
    return (i2c_reg[I2C_STATUS] >> 2) & 1;
}

bool is_transfer_done() {
    return (i2c_reg[I2C_STATUS] >> 1) & 1;
}

void reset_transfer_done() {
    i2c_reg[I2C_STATUS] |= (1 >> 1);
}

bool is_transfer_active() {
    return (i2c_reg[I2C_STATUS] >> 0) & 1;
}

void reset_status_register() {
    reset_CLKT();
    reset_ERR();
    reset_transfer_done();
}

/**
 * Data length register
 */

void set_data_length(int num) {
    i2c_reg[I2C_DLEN] = num;
}

uint16_t get_data_length() {
    return (i2c_reg[I2C_DLEN] << 16);
}

/**
 * Slave address register
 */

void set_slave_address(uint8_t address) {
    i2c_reg[I2C_SLAVE_ADDRESS] = address & 0x7F; 
}

uint8_t get_slave_address() {
    return (i2c_reg[I2C_SLAVE_ADDRESS] << 25) & 0x7F; 
}

/**
 * Clock divider register
 */

void set_clock_divider(uint16_t divisor) {
    i2c_reg[CLOCK_DIVIDER] ^= divisor;
}

uint16_t get_clock_divider() {
    return (i2c_reg[CLOCK_DIVIDER] << 16);
}

/**
 * Data delay register
 */

void set_falling_edge_delay(uint16_t delay) {
    i2c_reg[DATA_DELAY] ^= (delay << 16);
}

uint16_t get_falling_edge_delay() {
    return (i2c_reg[DATA_DELAY] >> 16);
}

void set_rising_edge_delay(uint16_t delay) {
    i2c_reg[DATA_DELAY] ^= delay;
}

uint16_t get_rising_edge_delay() {
    return (i2c_reg[DATA_DELAY] << 16);
}

/**
 * Clock stretch timeout register
 */

void set_clock_stretch_timeout(uint16_t timeout) {
    i2c_reg[CLOCK_STRETCH_TIMEOUT] ^= timeout;
}

uint16_t get_clock_stretch_timeout() {
    return (i2c_reg[CLOCK_STRETCH_TIMEOUT] << 16);
}

/**
 * Data FIFO register
 */

uint8_t read_byte_from_FIFO() {
    return (i2c_reg[DATA_FIFO] & 0xFF);
}

void write_bytes_to_FIFO(uint8_t *bytes, uint16_t no_bytes) {
    uint16_t i;
    for (i=0; (i<no_bytes) && (i<16); i++) {
        i2c_reg[DATA_FIFO] = (*(bytes+i) & 0xFF);
    }
}

uint32_t read_status_reg() {
    return i2c_reg[I2C_STATUS];
}

void read_bytes(uint8_t address, uint8_t *bytes, int no_bytes) {
    reset_status_register();
    clear_FIFO_data();

    set_slave_address(address);
    set_data_length(no_bytes);
    set_read_transfer();
    start_transfer();

    while (!is_transfer_done()) {
        // Check if the FIFO is full but not all the data has been transmitted
        if (does_RX_need_reading()) {
            uint16_t i;
            for (i=0; i<16; i++) {
                *bytes = read_byte_from_FIFO();
                bytes++;
                no_bytes--;
            }
        } 
        else if (is_ERR()) {
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
    reset_status_register();
    clear_FIFO_data();
}

void write_bytes(uint8_t address, uint8_t *bytes, uint16_t no_bytes) {
    reset_status_register();
    clear_FIFO_data();

    set_slave_address(address);
    
    write_bytes_to_FIFO(bytes, no_bytes);    
    
    set_data_length(no_bytes);

    set_write_transfer();
    start_transfer();   

    while(!is_transfer_done()) {
        // check if the FIFO is empty but not all the data has been transmitted
        if (does_TX_need_writing) {
            no_bytes -= 16;
            bytes += 16;
            write_bytes_to_FIFO(bytes, no_bytes);
        }
        else if (is_ERR()) {
            //NACK
            break;
        }
    }
    reset_status_register();
    clear_FIFO_data();
}

