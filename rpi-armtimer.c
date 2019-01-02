/*
    Part of the Raspberry-Pi Bare Metal Tutorials
    https://www.valvers.com/rpi/bare-metal/
    Copyright (c) 2013-2018, Brian Sidebotham
    This software is licensed under the MIT License.
    Please see the LICENSE file included with this software.
*/

#include "rpi-armtimer.h"

static rpi_arm_timer_t* rpiArmTimer = (rpi_arm_timer_t*)RPI_ARMTIMER_BASE;

rpi_arm_timer_t* RPI_GetArmTimer(void)
{
    return rpiArmTimer;
}

uint32_t RPI_GetTimerValue() {
    return (*rpiArmTimer).Value;
}

void micros(uint32_t delay) {
    uint32_t previousValue = RPI_GetTimerValue();
    
    while (delay > previousValue) {
        while (RPI_GetTimerValue() > 0);
        delay -= previousValue;
        previousValue = RPI_GetTimerValue();
    }

    while (previousValue - RPI_GetTimerValue() < delay);
}

void enable_timer(uint32_t delay) {
    RPI_GetArmTimer()->Control |= RPI_ARMTIMER_CTRL_INT_ENABLE;
    RPI_GetArmTimer()->Load = delay;
}

void armtimer_interrupt_handler() {
    if (RPI_GetArmTimer()->RAWIRQ & 1) {
        RPI_GetArmTimer()->IRQClear = 1;
        if (wii_classic_update) read_WiiClassic(0);
        if (ws2812b_update_needed) {
            ws2812b_turnoff();
            ws2812b_enable_pixel(LY);
            ws2812b_update();
        }
    }
}
