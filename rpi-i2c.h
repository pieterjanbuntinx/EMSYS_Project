#ifndef RPI_I2C_H
#define RPI_I2C_H

#include <stdint.h>
#include <stdbool.h>

static volatile unsigned int* i2c_reg;

typedef struct 
{
    volatile uint32_t C;
    volatile uint32_t S;
    volatile uint32_t DLEN;
    volatile uint32_t A;
    volatile uint32_t FIFO;
    volatile uint32_t DIV;
    volatile uint32_t DEL;
    volatile uint32_t CLKT;
} rpi_i2c_controller_t;

#define I2C_C_I2CEN	(1 << 15)
#define I2C_C_INTR	(1 << 10)
#define I2C_C_INTT	(1 <<  9)
#define I2C_C_INTD	(1 <<  8)
#define I2C_C_ST	(1 <<  7)
#define I2C_C_CLEAR	(1 <<  5)
#define I2C_C_READ	(1 <<  0)

#define I2C_S_CLKT	(1 << 9)
#define I2C_S_ERR	(1 << 8)
#define I2C_S_RXF	(1 << 7)
#define I2C_S_TXE	(1 << 6)
#define I2C_S_RXD	(1 << 5)
#define I2C_S_TXD	(1 << 4)
#define I2C_S_RXR	(1 << 3)
#define I2C_S_TXW	(1 << 2)
#define I2C_S_DONE	(1 << 1)
#define I2C_S_TA	(1 << 0)

#define START_READ    I2C_C_I2CEN|I2C_C_ST|I2C_C_CLEAR|I2C_C_READ
#define START_WRITE    I2C_C_I2CEN|I2C_C_ST

rpi_i2c_controller_t* RPI_GetI2CController();

void reset_status_register();
void clear_FIFO_data();

uint8_t read_byte_from_FIFO();
void write_bytes_to_FIFO(uint8_t *, uint16_t);
uint32_t read_status_reg();

/**
 * 
 */

void read_bytes(uint8_t , uint8_t *, uint16_t );
void write_bytes(uint8_t , uint8_t *, uint16_t );
int read_bytes_int(uint8_t address, uint8_t *bytes, uint16_t no_bytes);
int write_bytes_int(uint8_t address, uint8_t *bytes, uint16_t no_bytes);
void i2c_interrupt_handler();

#endif
