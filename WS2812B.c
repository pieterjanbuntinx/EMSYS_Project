#include "WS2812B.h"

#define SYMBOL_HIGH     0x6 // 1 1 0
#define SYMBOL_LOW      0x4 // 1 0 0
#define RESET_DELAY_US  60

uint8_t data_pin;
uint8_t no_pixels;
uint32_t *pixels = 0;
volatile bool int_continue = true;

void init_ws2812b(uint8_t pin, uint8_t num_pixels) {
    data_pin = pin;
    no_pixels = num_pixels;
    uint8_t i;
    for (i = 0; i<no_pixels; i++) {
        pixels[i] = 0;
    }

    /** Setup the pwm controller */
	RPI_GetPWMController()->ctl =
			RPI_PWM_CTL_USEF1 | 
			RPI_PWM_CTL_CLRF1 |
			RPI_PWM_CTL_MODE1;
}

void ws2812b_setColor(uint8_t red, uint8_t green, uint8_t blue, uint16_t led) {
    pixels[led] = (green << 16) | (red << 8) | (blue << 0);
}

void test_pwm() {
    RPI_GetPWMController()->fif1 = 0xFF00FFAB;
    micros(10);
    RPI_GetPWMController()->ctl |= RPI_PWM_CTL_PWEN1;
}

void ws2812b_update() {
    uint8_t fifo_bits_counter = 0;
    uint32_t fifo_value = 0;
    uint16_t i;
    for (i=0; i<no_pixels; i++) {
        if (fifo_bits_counter + 24 <= 32) {
            fifo_value |= ((pixels[i] & 0xFFFFFF) << 8-fifo_bits_counter);
            fifo_bits_counter += 24;
        } else if (fifo_bits_counter == 32) {
            RPI_GetPWMController()->fif1 = fifo_value;
            fifo_bits_counter = 0;
            fifo_value = 0;
        } else {
            fifo_bits_counter += 24 - 32;
            fifo_value |= (pixels[i] >> (24 - fifo_bits_counter));
            RPI_GetPWMController()->fif1 = fifo_value;
            fifo_value = pixels[i] << (8+24-fifo_bits_counter);
        }
    }
    RPI_GetPWMController()->ctl |= RPI_PWM_CTL_PWEN1;
    while(!(RPI_GetPWMController()->sta & RPI_PWM_STA_EMPT1));
    micros(RESET_DELAY_US);
}
