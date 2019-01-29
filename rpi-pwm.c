#include "rpi-pwm.h"

volatile unsigned int *clk;
volatile unsigned int *pwm;

volatile unsigned int* RPI_GetPWMController(void) {
    return pwm;
}

int init_pwm_hardware(){
    clk = (unsigned int*) RPI_CLOCK_BASE;
    pwm = (unsigned int*) RPI_PWM_BASE;

    // stop clock and waiting for busy flag doesn't work, so kill clock
    *(clk + RPI_PWMCLK_CNTL) = 0x5A000000 | (1 << 5);
    micros(10);
    
    uint16_t idiv = 84; 

    //shift idiv by 13 instead of 12, 12 doesn't seem to work
    *(clk + RPI_PWMCLK_DIV) = 0x5A000000 | (idiv << 13); // 240 MHz / 84 -> 0,350 us/bit

    // source=PLLD and enable clock
    *(clk + RPI_PWMCLK_CNTL) = 0x5A000016;
    
    //disable pwm
    *(pwm + RPI_PWM_CTL) = 0;
    micros(10);

	*(pwm + RPI_PWM_RNG1) = 32;
    micros(10);
    //enable pwm, turn on serializer mode and use FIFO
    //*(pwm + PWM_CTL) = RPI_PWM_CTL_PWEN1 | RPI_PWM_CTL_MODE1 | RPI_PWM_CTL_USEF1;
    return true;
}

//0b110, 0b100 100100100100100100100100 110110110110110110110110
void test_pwm() {
    *(pwm + RPI_PWM_CTL) = RPI_PWM_CTL_CLRF1;
    micros(100);
    
    *(pwm + RPI_PWM_FIF1) = 0b11011011011011011011011010010010;
    *(pwm + RPI_PWM_FIF1) = 0b01001001001001001001001001001001;
    *(pwm + RPI_PWM_FIF1) = 0b00100100100100100100100100100100;
    *(pwm + RPI_PWM_FIF1) = 0b11011011011011011011011010010010;
    *(pwm + RPI_PWM_FIF1) = 0b01001001001001001001001001001001;
    *(pwm + RPI_PWM_FIF1) = 0b00100100100100100100100100100100;
    *(pwm + RPI_PWM_FIF1) = 0b11011011011011011011011011011011;
    *(pwm + RPI_PWM_FIF1) = 0b01101101101101101001001001001001;
    *(pwm + RPI_PWM_FIF1) = 0b00100100100100100100100100100100;
    *(pwm + RPI_PWM_FIF1) = 0b10010010010010010010010011011011;
    *(pwm + RPI_PWM_FIF1) = 0b01101101101101101001001001001001;
    *(pwm + RPI_PWM_FIF1) = 0b00100100100100100100100100100100;
    *(pwm + RPI_PWM_FIF1) = 0b10010010010010010010010011011011;
    *(pwm + RPI_PWM_FIF1) = 0b01101101101101100000000000000000;

    *(pwm + RPI_PWM_CTL) = RPI_PWM_CTL_PWEN1 | RPI_PWM_CTL_MODE1 | RPI_PWM_CTL_USEF1;
    while (!(*(pwm + RPI_PWM_STA) & RPI_PWM_STA_EMPT1));
    *(pwm + RPI_PWM_CTL) = 0;
}


