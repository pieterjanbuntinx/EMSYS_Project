#include "WS2812B.h"

uint8_t pixel_data[no_pixels*3];
bool pixel_enable[no_pixels];

void init_ws2812b(uint8_t pin) {
    set_GPIO_alterfunc(&gpio[pin], 0b010);
    ws2812b_update_needed = true;

    /** Setup the pwm controller */
	*(RPI_GetPWMController()+RPI_PWM_CTL) =
			RPI_PWM_CTL_USEF1 | 
			RPI_PWM_CTL_CLRF1 |
			RPI_PWM_CTL_MODE1;

    ws2812b_turnoff();
}

void ws2812b_setpixel(uint8_t red, uint8_t green, uint8_t blue, bool enable, uint16_t led) {
    pixel_enable[led] = enable;
    pixel_data[3*led] = green;
    pixel_data[3*led+1] = red;
    pixel_data[3*led+2] = blue;
}

void ws2812b_disable_pixel(uint16_t led) {
    pixel_enable[led] = false;
}

void ws2812b_enable_pixel(uint16_t led) {
    pixel_enable[led] = true;
}

void ws2812b_update() {
    ws2812b_update_needed = false;
    _lock();
    *(RPI_GetPWMController() + RPI_PWM_CTL) = RPI_PWM_CTL_CLRF1;
    uint32_t fifo_reg = 0;
    uint16_t pixel;
    uint8_t fifo_reg_bit = 32;
    uint8_t fifo_reg_count = 0;
    
    for (pixel = 0; pixel<(no_pixels*3); pixel+=3) {
        uint8_t green, red, blue;
        if (pixel_enable[pixel/3]) {
            green = pixel_data[pixel];
            red = pixel_data[pixel+1];
            blue = pixel_data[pixel+2];
        } else {
            green = 0;
            red = 0;
            blue = 0;
        }
        //uprintf("red: %d, green: %d, blue: %d, pixel: %d\n\r", red, green, blue, pixel);

        uint8_t ibit;
        for (ibit = 24; ibit>0; ibit--) {
            bool bit;
            if (ibit > 15) {
                bit = green & (1 << (ibit-1-16));
            } else if (ibit > 8) {
                bit = red & (1 << (ibit-1-8));
            } else {
                bit = blue & (1 << ibit-1);
            }

            uint8_t symbol;
            if (bit) symbol = SYMBOL_HIGH;
            else symbol = SYMBOL_LOW;

            uint8_t isymbol;
            for (isymbol=0; isymbol<3; isymbol++) {
                if (fifo_reg_bit < 1) {
                    *(RPI_GetPWMController() + RPI_PWM_FIF1) = fifo_reg;
                    fifo_reg = 0;
                    fifo_reg_bit = 32;
                    fifo_reg_count++;
                    *(RPI_GetPWMController() + RPI_PWM_CTL) = RPI_PWM_CTL_PWEN1 | RPI_PWM_CTL_MODE1 | RPI_PWM_CTL_USEF1;
                }

                bool sym = symbol & (1 << (2-isymbol));
                if (sym) fifo_reg |= 1 << (fifo_reg_bit-1);
                fifo_reg_bit--;
            }
        }
        while(*(RPI_GetPWMController()+RPI_PWM_STA) & RPI_PWM_STA_FULL1);
        //micros(10*1000);
    }

    *(RPI_GetPWMController() + RPI_PWM_CTL) = RPI_PWM_CTL_PWEN1 | RPI_PWM_CTL_MODE1 | RPI_PWM_CTL_USEF1;
    while(!(*(RPI_GetPWMController()+RPI_PWM_STA) & RPI_PWM_STA_EMPT1));
    *(RPI_GetPWMController() + RPI_PWM_CTL) = 0;
    ws2812b_update_needed = true;
    _unlock();
    micros(RESET_DELAY_US);
}

// void ws2812b_debug() {
//     uprintf("ws2812b_debug\n\r");
//     micros(100*1000);
    
//     uint32_t fifo_reg = 0;
//     uint16_t pixel;
//     uint8_t fifo_reg_bit = 32;
//     for (pixel = 0; pixel<(no_pixels+1)*3; pixel+=3) {
//         uint8_t green = pixel_data[pixel];
//         uint8_t red = pixel_data[pixel+1];
//         uint8_t blue = pixel_data[pixel+2];
//         uprintf("pixel num: %d, Green: %x, Blue: %x, Red: %x\n\r", pixel/3, green, blue, red);
//         micros(100*1000);

//         uint8_t ibit;
//         for (ibit = 24; ibit>0; ibit--) {
//             bool bit;
//             if (ibit > 15) {
//                 bit = green & (1 << (ibit-1-16));
//             } else if (ibit > 8) {
//                 bit = red & (1 << (ibit-1-8));
//             } else {
//                 bit = blue & (1 << ibit-1);
//             }

//             uprintf("bit: %d, ", bit);
//             micros(100*1000);

//             uint8_t symbol;
//             if (bit) symbol = SYMBOL_HIGH;
//             else symbol = SYMBOL_LOW;

//             uprintf("symbol: %d, ", symbol);
//             micros(1000*100);

//             uint8_t isymbol;
//             for (isymbol=0; isymbol<3; isymbol++) {
//                 /**micros(1000*100);
//                 uprintf("iterate symbol bits, iteration: %d\n\r", isymbol);
//                 micros(1000*100);*/
//                 if (fifo_reg_bit < 1) {
//                     uprintf("\n\rfifo reg full: %x%x\n\r", (fifo_reg >> 16), (fifo_reg & 0x0000FFFF));
//                     fifo_reg = 0;
//                     fifo_reg_bit = 32;
//                 }

//                 bool sym = symbol & (1 << (2-isymbol));
//                 if (sym) fifo_reg |= 1 << (fifo_reg_bit-1);
//                 fifo_reg_bit--;
//             }
//         }
//         uprintf("end of pixel num %d\n\r", pixel/3);
//         micros(100*1000);
//     }
// }

void ws2812b_turnoff() {
    uint16_t i;
    for (i = 0; i<no_pixels; i++) {
        pixel_enable[i] = false;
    }
}





