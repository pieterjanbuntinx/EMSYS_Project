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

	set_GPIO_output(&gpio[LED_pin]);
	
	RPI_GetIrqController()->Enable_IRQs_2 = RPI_IRQ_2_ARM_UART_IRQ;	
	RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;
	RPI_GetIrqController()->Enable_IRQs_2 = RPI_IRQ_2_ARM_I2C_IRQ;

	/* Initialize uart and allow uart to send interrupts */
	uart_init();				// initialize UARTs

	/* Enable interrupts */
	_unlock();

	/* Setup the system timer interrupt */
    /* Timer frequency = Clk/CTRL_PRESCALE * Load */
    RPI_GetArmTimer()->Load = 0xFFFFFFFF;

    /* Setup the ARM Timer */
    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_1;
			

	uprintf("Started reading range data...\r\n");
	micros(100*1000);

	init_WiiClassic();

	init_pwm_hardware();
	init_ws2812b(WS2812B_pin);

	uint16_t i;
	for (i = 0; i<no_pixels; i++) {
		ws2812b_setColor(0, 0, 255, 20, true, i);
	}

	ws2812b_update_needed=false;

	
	//enable_timer(10000); // refresh pixels and wiiclassic 100 times/s

	while (1) {
		ws2812b_update();
		micros(10000);
	}
}
