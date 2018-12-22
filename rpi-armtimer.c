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

void micros(uint32_t delay) {
    uint32_t previousValue = (*rpiArmTimer).Value;
    
    while (delay > previousValue) {
        while ((*rpiArmTimer).Value > 0);
        delay -= previousValue;
        previousValue = (*rpiArmTimer).Value;
    }

    while (previousValue - (*rpiArmTimer).Value < delay);
}
