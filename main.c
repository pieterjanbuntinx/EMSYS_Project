/********************************************************************
Main file inspired by the armc-013.c file from the Raspberry-Pi Bare
Metal Tutorials by Brian Sidebotham and modified to implement an
interrupt-driven device driver for the Raspberry Pi 1 Model b+.
********************************************************************/

#include "rpi-interrupts.h" 
#include "rpi-gpio.h"
#include "rpi-uart.h"
#include "rpi-i2c.h"
#include "rpi-armtimer.h"
#include <stdint.h>
#include "WiiClassic.h"

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

	//init_WiiClassic();
	//read_WiiClassic(0);

	//uint8_t bytes[] = { 0xFF, 0xFA, 0x12, 0xAB };
	//uint8_t *bytes2;
    set_clock_divider(CDIV_10kHz);

	writeReg(0xF0, 0x55);
    writeReg(0xFB, 0x00);

	uint8_t byte[] = {0};
	uint8_t* bytes;

	while (1) {
		delay(100000);
		set_pin(&gpio[LED_pin]);
		read_WiiClassic(0);
		clear_pin(&gpio[LED_pin]);
	}
}
