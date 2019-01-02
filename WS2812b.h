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

#define SYMBOL_HIGH     0x6 // 1 1 0
#define SYMBOL_LOW      0x4 // 1 0 0
#define RESET_DELAY_US  100
#define no_pixels       62

bool ws2812b_update_needed;

void init_ws2812b(uint8_t pin);
void ws2812b_setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness, bool enable, uint16_t led);
void ws2812b_update();
void ws2812b_turnoff();
void ws2812b_disable_pixel(uint16_t led);
void ws2812b_enable_pixel(uint16_t led);
void ws2812b_debug();

#endif

