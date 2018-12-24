#ifndef WS2812B_H
#define WS2812B_H

#include "defines.h"
#include "rpi-gpio.h"
#include "rpi-armtimer.h"
#include "rpi-uart.h"
#include "rpi-pwm.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

void init_ws2812b(uint8_t pin, uint8_t num_pixels);
void ws2812b_setColor(uint8_t red, uint8_t green, uint8_t blue, uint16_t led);
void test_pwm();
void ws2812b_update();

#endif

