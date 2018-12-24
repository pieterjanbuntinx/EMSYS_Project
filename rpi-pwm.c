#include "rpi-pwm.h"

rpi_pwm_controller_t *pwm_controller = (rpi_pwm_controller_t*) PWM_BASE;

rpi_pwm_controller_t* RPI_GetPWMController(void) {
    return pwm_controller;
}


