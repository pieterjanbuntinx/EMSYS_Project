#include "WS2812b.h"

void ws2812b_handler() {
    if (1) return;
    RPI_GetArmTimer()->IRQClear = 1;    
}
