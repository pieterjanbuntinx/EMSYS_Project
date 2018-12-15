//
// Based on https://github.com/bitbank2/VL53L0X which 
// is based on Pololu's Arduino library 
// https://github.com/pololu/vl53l0x-arduino
//
//

#ifndef VL53L0X_h
#define VL53L0X_h

#define I2C_SLAVE 0x29

void usleep(unsigned long val);

//
// Read the model and revision of the
// tof sensor
//
int tofGetModel(int *model, int *revision);

//
// Read the current distance in mm
//
int tofReadDistance(void);

//
// Opens a file system handle to the I2C device
// sets the device continous capture mode
//
int tofInit(int iChan, int iAddr, int bLongRange);

#endif
