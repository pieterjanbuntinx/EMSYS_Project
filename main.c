/********************************************************************
Main file inspired by the armc-013.c file from the Raspberry-Pi Bare
Metal Tutorials by Brian Sidebotham and modified to implement an
interrupt-driven device driver for the Raspberry Pi 1 Model b+.
********************************************************************/

#include "rpi-interrupts.h" 
#include "rpi-gpio.h"
#include "rpi-uart.h"
#include "rpi-i2c.h"
#include "VL53L0X.h"
#include "rpi-armtimer.h"
#include <stdint.h>

#define ADDRESS_DEFAULT 0b0101001 // VL53L0X default address

const int TX_pin = 14;
const int RX_pin = 15;

const int SDA_pin = 2;
const int SCL_pin = 3;

const int LED_pin = 18;

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
	gpio_init();

	set_GPIO_pullup(&gpio[SDA_pin]);
	set_GPIO_pullup(&gpio[SCL_pin]);

	set_GPIO_alterfunc(&gpio[TX_pin], 4);
	set_GPIO_alterfunc(&gpio[RX_pin], 4);
	
	set_GPIO_alterfunc(&gpio[SDA_pin], 4);
	set_GPIO_alterfunc(&gpio[SCL_pin], 4);

	set_GPIO_output(&gpio[LED_pin]);

	RPI_GetIrqController()->Enable_IRQs_2 = RPI_IRQ_2_ARM_UART_IRQ;	

	/* Initialize uart and allow uart to send interrupts */
	uart_init();				// initialize UARTs

	/* Enable interrupts */
	_unlock();

	/* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    RPI_GetArmTimer()->Load = 0x400;

    /* Setup the ARM Timer */
    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;

	i2c_init();

	uprintf("Started reading range data...\r\n");


// 	/**int bytes[] = {0xFF, 0xFA, 0xFB, 0xFC};
// 	write_bytes(I2C_SLAVE_ADDRESS, bytes, 3);
// 	read_bytes(I2C_SLAVE_ADDRESS, )*/
//  ///**
// 	int i;
// 	int iDistance;
// 	int model, revision;

// 	// For Raspberry Pi's, the I2C channel is usually 1
// 	// For other boards (e.g. OrangePi) it's 0
// 	i = tofInit(0, 0x29, 0); // set long range mode (up to 2m)
// 	if (i != 1)
// 	{
// 		uprintf("There's a problem --> quit \r\n");
// 		return; // problem - quit
// 	}
// 	uprintf("VL53L0X device successfully opened.\r\n");
//  	i = tofGetModel(&model, &revision);
// 	uprintf("Model ID - %d\n", model);
// 	uprintf("Revision ID - %d\n", revision);

// 	for (i=0; i<1200; i++) // read values 20 times a second for 1 minute
// 	{
// 		iDistance = tofReadDistance();
// 		if (iDistance < 4096) // valid range?
// 			uprintf("Distance = %dmm\n", iDistance);
// 		usleep(50000); // 50ms
// 	}
// */
}
