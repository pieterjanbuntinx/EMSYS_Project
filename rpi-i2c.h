#ifndef RPI_I2C_H
#define RPI_I2C_H

#include <stdint.h>
#include <stdbool.h>

static volatile unsigned int* i2c_reg;

/**
 * Control register
*/

extern void i2c_init();
extern void i2c_enable();
extern void i2c_disable();
extern void enable_int_RX();
extern void disable_int_RX();
extern void enable_int_TX();
extern void disable_int_TX();
extern void enable_int_DONE();
extern void enable_int_DONE();
extern void start_transfer();
extern void clear_FIFO_data();
extern void set_read_transfer();
extern void set_write_transfer();

/**
 * Status register
*/

extern bool is_CLKT();
extern void reset_CLKT();
extern bool is_ERR();
extern void reset_ERR();
extern bool is_RX_FIFO_full();
extern bool is_TX_FIFO_empty();
extern bool does_RX_contain_DATA();
extern bool does_TX_accept_DATA();
extern bool does_RX_need_reading();
extern bool does_TX_need_writing();
extern bool is_transfer_done();
extern bool is_transfer_active();

/**
 * Data length register
 */

extern void set_data_length(int num);
extern uint16_t get_data_length();

/**
 * Slave address register
 */

extern void set_slave_address(uint8_t address);
extern uint8_t get_slave_address();

/**
 * Clock divider register
 */

extern void set_clock_divider(uint16_t divisor);
extern uint16_t get_clock_divider();

/**
 * Data delay register
 */

extern void set_falling_edge_delay(uint16_t delay);
extern uint16_t get_falling_edge_delay();
extern void set_rising_edge_delay(uint16_t delay);
extern uint16_t get_rising_edge_delay();

/**
 * Clock stretch timeout register
 */

extern void set_clock_stretch_timeout(uint16_t timeout);
extern uint16_t get_clock_stretch_timeout();

/**
 *  FIFO register
 */

uint8_t read_byte_from_FIFO();
void write_bytes_to_FIFO(uint8_t *, uint16_t);
uint32_t read_status_reg();

/**
 * 
 */

void read_bytes(uint8_t , uint8_t *, int );
void write_bytes(uint8_t , uint8_t *, uint16_t );

#endif
