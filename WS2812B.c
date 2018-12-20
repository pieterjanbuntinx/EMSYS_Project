#include "WS2812B.h"

int status = 1;

void ws2812b_handler() {
    //if (RPI_getRAWIRQ() & 0b1) {
        if (status) {
            clear_pin(&gpio[18]);
        } else {
            set_pin(&gpio[18]);
        }
        RPI_GetArmTimer()->IRQClear = 1;
   // } 
}
