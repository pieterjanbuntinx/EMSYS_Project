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
#include "WS2812B.h"
#include "rpi-pwm.h"

#define TX_pin 14
#define RX_pin 15

#define SDA_pin 2
#define SCL_pin 3

#define LED_pin 23
#define WS2812B_pin 18 

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
	gpio_init();

	set_GPIO_pullup(&gpio[SDA_pin]);
	set_GPIO_pullup(&gpio[SCL_pin]);

	set_GPIO_alterfunc(&gpio[TX_pin], 4);
	set_GPIO_alterfunc(&gpio[RX_pin], 4);
	
	set_GPIO_alterfunc(&gpio[SDA_pin], 4);
	set_GPIO_alterfunc(&gpio[SCL_pin], 4);

	set_GPIO_alterfunc(&gpio[WS2812B_pin], 0b010);
	set_GPIO_output(&gpio[LED_pin]);
	
	RPI_GetIrqController()->Enable_IRQs_2 = RPI_IRQ_2_ARM_UART_IRQ;	
	//RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;
	RPI_GetIrqController()->Enable_IRQs_2 = RPI_IRQ_2_ARM_I2C_IRQ;

	/* Initialize uart and allow uart to send interrupts */
	uart_init();				// initialize UARTs

	/* Enable interrupts */
	_unlock();

	/* Setup the system timer interrupt */
    /* Timer frequency = Clk/CTRL_PRESCALE * Load */
    RPI_GetArmTimer()->Load = 1;

    /* Setup the ARM Timer */
    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_1;
			

	uprintf("Started reading range data...\r\n");

	init_WiiClassic();

	/**init_ws2812b(WS2812B_pin, 3);

	ws2812b_setColor(0xFF, 0, 0, 0);
	ws2812b_setColor(0, 0xFF, 0, 1);
	ws2812b_setColor(0, 0, 0xFF, 2);*/

	while (1) {
		micros(10000);
		read_WiiClassic(0);
		micros(10000);
		print_WiiClassic();
		//ws2812b_update();
		//test_pwm();
	}
}
