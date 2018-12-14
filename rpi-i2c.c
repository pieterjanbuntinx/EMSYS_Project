#include "rpi-i2c.h"
#include "defines.h"
#include "rpi-uart.h"

//http://www.susa.net/wordpress/2012/06/raspberry-pi-pcf8563-real-time-clock-rtc/

struct bcm2835_peripheral bsc0 = {I2C_BASE};

int read_from_FIFO() {
    return (BSC0_FIFO & 0xFF);
}

void write_to_FIFO(unsigned int *bytes, unsigned int no_bytes) {
    unsigned int i;
    for (i = 0; i<16 && i<no_bytes; i++) {
        BSC0_FIFO = *(bytes + i) & 0xFF;
    }
}

void wait_i2c_done() {
        //Wait till done, let's use a timeout just in case
        int timeout = 50;
        while((!((BSC0_S) & BSC_S_DONE)) && --timeout) {
            unsigned int i;
            for (i=0; i<1000; i++);
        }
        if(timeout == 0)
            uprintf("wait_i2c_done() timeout. Something went wrong.\n");
}

void read_bytes(unsigned int address, unsigned int *bytes, unsigned int no_bytes) {
    BSC0_A = address;
    BSC0_DLEN = no_bytes;
    BSC0_S = START_READ;

    while(!(BSC0_S & BSC_S_DONE)) {
        // check if FIFO is full and needs reading
        if (BSC0_S & BSC_S_RXR) {
            unsigned int i;
            for(i=0; i<16; i++) {
                *bytes = read_from_FIFO();
                bytes++;
                no_bytes--;
            }
        } 
        else if (BSC0_S & BSC_S_ERR) {
            //NACK received, something went wrong
            break;
        }
    }

    unsigned int i;
    for(i=0; i<no_bytes; i++) {
        *bytes = read_from_FIFO();
        bytes++;
    }

}

void write_bytes(unsigned int address, unsigned int *bytes, unsigned int no_bytes) {
    BSC0_A = address;
    BSC0_DLEN = no_bytes;

    write_to_FIFO(bytes, no_bytes);

    BSC0_S = CLEAR_STATUS;
    BSC0_C = START_WRITE;

    while(!(BSC0_S & BSC_S_DONE)) {
        // check if the FIFO can be filled again
        if (BSC0_S & BSC_S_TXW) {
            no_bytes -= 16;
            bytes += 16;
            write_to_FIFO(bytes, no_bytes);
        }
        else if (BSC0_S & BSC_S_ERR) {
            break;
        }
    }

}

int getAddress() {
    return *bsc0.addr;
}

/**
void read_bytes(unsigned int address, unsigned int *bytes, unsigned int no_bytes) {
    set_data_length(no_bytes);
    set_slave_address(address);
    set_read_transfer();

    start_transfer();

    while(!is_transfer_active());
    while(!is_transfer_done()) {
        if(does_RX_contain_DATA()) {
            int i = 0;
            for (i=0; i < 16; i++) {
                *bytes = get_FIFO_data();
                bytes++;
                no_bytes--;
            }
        }
        else if (is_ERR()) break; //received NACK, end transmission
    }

    unsigned int i;
    for (i=0; i<no_bytes; i++) {
        *bytes = get_FIFO_data();
        bytes++;
    }
}

void write_bytes(unsigned int address, unsigned int *bytes, unsigned int no_bytes) {
    reset_status_register();
    clear_FIFO_data();

    set_data_length(no_bytes);

    unsigned int i;
    for (i = 0; i<no_bytes; i++) { 
        set_FIFO_data(bytes[i]);
    }
    set_slave_address(address);
    set_write_transfer();
    start_transfer();   
    while(!is_transfer_done());
}
*/

