#ifndef I2C_H
#define I2C_H

typedef struct 
{
    volatile unsigned int C;
    volatile unsigned int S;
    volatile unsigned int DLEN;
    volatile unsigned int A;
    volatile unsigned int FIFO;
    volatile unsigned int DIV;
    volatile unsigned int DEL;
    volatile unsigned int CLKT;
} rpi_i2c_controller;

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

unsigned int * data_buffer;

void I2C_write(unsigned int bytes, unsigned int slave_addr, unsigned int * data);
void i2c_read_register(unsigned int bytes, unsigned int slave_addr, unsigned int reg_addr, unsigned int * buffer);

unsigned int I2C_get_DONE();
unsigned int I2C_get_TXW();
unsigned int I2C_get_RXR();

void I2C_handle_DONE();
void I2C_handle_RXR();
void I2C_handle_TXW();
void I2C_setup();
#endif