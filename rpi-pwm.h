#ifndef RPI_PWM_H
#define RPI_PWM_H

#include "defines.h"
#include "rpi-gpio.h"
#include "rpi-armtimer.h"
#include "rpi-uart.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define PWM_BASE (PERIPHERAL_BASE + 0x20C000)

typedef struct
{
    volatile uint32_t ctl;
#define RPI_PWM_CTL_MSEN2                        (1 << 15)
#define RPI_PWM_CTL_USEF2                        (1 << 13)
#define RPI_PWM_CTL_POLA2                        (1 << 12)
#define RPI_PWM_CTL_SBIT2                        (1 << 11)
#define RPI_PWM_CTL_RPTL2                        (1 << 10)
#define RPI_PWM_CTL_MODE2                        (1 << 9)
#define RPI_PWM_CTL_PWEN2                        (1 << 8)
#define RPI_PWM_CTL_MSEN1                        (1 << 7)
#define RPI_PWM_CTL_CLRF1                        (1 << 6)
#define RPI_PWM_CTL_USEF1                        (1 << 5)
#define RPI_PWM_CTL_POLA1                        (1 << 4)
#define RPI_PWM_CTL_SBIT1                        (1 << 3)
#define RPI_PWM_CTL_RPTL1                        (1 << 2)
#define RPI_PWM_CTL_MODE1                        (1 << 1)
#define RPI_PWM_CTL_PWEN1                        (1 << 0)
    volatile uint32_t sta;
#define RPI_PWM_STA_STA4                         (1 << 12)
#define RPI_PWM_STA_STA3                         (1 << 11)
#define RPI_PWM_STA_STA2                         (1 << 10)
#define RPI_PWM_STA_STA1                         (1 << 9)
#define RPI_PWM_STA_BERR                         (1 << 8)
#define RPI_PWM_STA_GAP04                        (1 << 7)
#define RPI_PWM_STA_GAP03                        (1 << 6)
#define RPI_PWM_STA_GAP02                        (1 << 5)
#define RPI_PWM_STA_GAP01                        (1 << 4)
#define RPI_PWM_STA_RERR1                        (1 << 3)
#define RPI_PWM_STA_WERR1                        (1 << 2)
#define RPI_PWM_STA_EMPT1                        (1 << 1)
#define RPI_PWM_STA_FULL1                        (1 << 0)
    volatile uint32_t dmac;
#define RPI_PWM_DMAC_ENAB                        (1 << 31)
#define RPI_PWM_DMAC_PANIC(val)                  ((val & 0xff) << 8)
#define RPI_PWM_DMAC_DREQ(val)                   ((val & 0xff) << 0)
    volatile uint32_t rng1;
    volatile uint32_t dat1;
    volatile uint32_t fif1;
    volatile uint32_t rng2;
    volatile uint32_t dat2;
} rpi_pwm_controller_t;

extern rpi_pwm_controller_t* RPI_GetPWMController(void);

#endif
