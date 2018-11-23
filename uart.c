/********************************************************************
Main file inspired by the armc-013.c file from the Raspberry-Pi Bare
Metal Tutorials by Brian Sidebotham and modified to implement an
interrupt-driven device driver for the Raspberry Pi 1 Model b+.
********************************************************************/

#include "rpi-interrupts.h" // other exception handlers
#include "rpi-gpio.h"
#include "rpi-uart.h"
#include "rpi-i2c.h"

#define VL53L0X_I2C_ADDRESS 0x52

const int TX_pin = 14;
const int RX_pin = 15;

const int SDA_pin = 2;
const int SCL_pin = 3;

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
	gpio_init();
	set_GPIO_alterfunc(&gpio[TX_pin], 4);
	set_GPIO_alterfunc(&gpio[RX_pin], 4);
	
	set_GPIO_alterfunc(&gpio[SDA_pin], 4);
	set_GPIO_alterfunc(&gpio[SCL_pin], 4);

	RPI_GetIrqController()->Enable_IRQs_2 = RPI_IRQ_2_ARM_UART_IRQ;	

	/* Initialize uart and allow uart to send interrupts */
	uart_init();				// initialize UARTs

	/* Enable interrupts */
	_unlock();

	char line[128];
	while(1){
		uprintf("Reading from ToF sensor...\n\r");
		char bytes[10];
		read_bytes(VL53L0X_I2C_ADDRESS, 5, &bytes);
		uprintf(bytes);
		uprintf("\n\r");
	}
}
