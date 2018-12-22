#include "WS2812B.h"

#define T0H 7
#define T1H 13
#define T0L 16
#define T1L 12
#define RES 60

static void output_1_pulse();
static void output_0_pulse();
static void reset();

uint8_t data_pin;
uint8_t no_pixels;
uint32_t *pixels = 0;

void init_ws2812b(uint8_t pin, uint8_t num_pixels) {
    data_pin = pin;
    no_pixels = num_pixels;
    uint8_t i;
    for (i = 0; i<no_pixels; i++) {
        pixels[i] = 0;
    }
}

void ws2812b_setColor(uint8_t red, uint8_t green, uint8_t blue, uint16_t led) {
    pixels[led] = (green << 16) | (red << 8) | (blue << 0);
}

static void output_1_pulse() {
    set_pin(&gpio[data_pin]);
    micros(T1H);
    clear_pin(&gpio[data_pin]);
    micros(T1L);
}

static void output_0_pulse() {
    set_pin(&gpio[data_pin]);
    micros(T0H);
    clear_pin(&gpio[data_pin]);
    micros(T0L);
}

static void reset() {
    micros(RES);
}

void ws2812b_update() {
    uint16_t i;
    for (i=0; i<no_pixels; i++) {
        int bit;
        for (bit = 23; bit>=0; bit--) {
            if (pixels[i] & (1 << bit)) {
                output_1_pulse();
            } else {
                output_0_pulse();
            }
        }
    }
    reset();
    
}
