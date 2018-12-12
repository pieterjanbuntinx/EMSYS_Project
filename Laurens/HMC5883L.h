#ifndef HMC5883L_H
#define HMC5883L_H

// HMC5883L Magnetometer base address
#define HMC5883L_BASE_READ   0x3D
#define HMC5883L_BASE_WRITE  0x3C
#define HMC5883L_SLAVE_ADDR  0x1E

/*
HMC5883L Register addresses
*/
#define	HMC5883L_REGISTER_MAG_CRA_REG_M            0x00	//Configuration Register A
#define HMC5883L_REGISTER_MAG_CRB_REG_M            0x01	//Configuration Register B
#define HMC5883L_REGISTER_MAG_MR_REG_M             0x02	//Mode Register
#define HMC5883L_REGISTER_MAG_OUT_X_H_M            0x03	//Data Output X MSB Register
#define HMC5883L_REGISTER_MAG_OUT_X_L_M            0x04	//Data Output X LSB Register
#define HMC5883L_REGISTER_MAG_OUT_Z_H_M            0x05	//Data Output Z MSB Register
#define HMC5883L_REGISTER_MAG_OUT_Z_L_M            0x06	//Data Output Z LSB Register
#define HMC5883L_REGISTER_MAG_OUT_Y_H_M            0x07	//Data Output Y MSB Register
#define HMC5883L_REGISTER_MAG_OUT_Y_L_M            0x08	//Data Output Y LSB Register
#define HMC5883L_REGISTER_MAG_SR_REG_Mg            0x09	//Status Register
#define HMC5883L_REGISTER_MAG_IRA_REG_M            0x0A	//Identification Register A
#define HMC5883L_REGISTER_MAG_IRB_REG_M            0x0B	//Identification Register B
#define HMC5883L_REGISTER_MAG_IRC_REG_M            0x0C	//Identification Register C
#define HMC5883L_REGISTER_MAG_TEMP_OUT_H_M         0x31
#define HMC5883L_REGISTER_MAG_TEMP_OUT_L_M         0x32
/*
Configuration Register A CRA - Data output rate and measurement configuration

CRA7 	= Reserved
CRA6:5 	= Number of samples (averaged) per measurement output
CRA4:2	= Data output rate bits. 
CRA1:0	= Measurement configuration bits

CRA default = 0x10 = 0001 0000 -> 1 sample per measurement, data output rate = 15, normal measurement configuration
*/
#define NUM_SAMPLES_1 	(0 << 5)	//Number of samples = 1
#define NUM_SAMPLES_2 	(1 << 5)	//Number of samples = 2
#define NUM_SAMPLES_4 	(2 << 5)	//Number of samples = 3
#define NUM_SAMPLES_8 	(3 << 5)	//Number of samples = 4
#define DOR_0_75		(0 << 2)	//Data Output Rate = 0.75 Hz
#define DOR_1_5			(1 << 2)	//Data Output Rate = 1.5  Hz
#define DOR_3			(2 << 2)	//Data Output Rate = 3    Hz
#define DOR_7_5			(3 << 2)	//Data Output Rate = 7.5  Hz
#define DOR_15			(4 << 2)	//Data Output Rate = 15   Hz
#define DOR_30			(5 << 2)	//Data Output Rate = 30   Hz
#define DOR_75			(6 << 2)	//Data Output Rate = 75   Hz
#define MM_NORMAL		(0 << 0)	//Normal measurement configuration
#define MM_POS_BIAS		(1 << 0)	//Positive bias configuration for X,Y and Z axes
#define MM_NEG_BIAS		(2 << 0)	//Negative bias configuration for X,Y and Z axes


/*
Configuration Register B CRB - Gain settings

Configuration register B sets the device gain.
Only the first 3 bits matter for this, the 5 LSB need to be 0!
*/
#define MAGGAIN_0_88 0x0	//Gain of 0.88, configuration bits 000 00000
#define MAGGAIN_1_3  0x20	//Gain of 1.3 , configuration bits 001 00000
#define MAGGAIN_1_9  0x40	//Gain of 1.9 , configuration bits 010 00000
#define MAGGAIN_2_5  0x60	//Gain of 2.5 , configuration bits 011 00000
#define MAGGAIN_4_0  0x80	//Gain of 4.0 , configuration bits 100 00000
#define MAGGAIN_4_7  0xA0	//Gain of 4.7 , configuration bits 101 00000
#define MAGGAIN_5_6  0xE0	//Gain of 5.6 , configuration bits 110 00000
#define MAGGAIN_8_1  0xC0	//Gain of 8.1 , configuration bits 111 00000

/*
Mode register MR - Operating mode of device

MR7	  = High speed mode
MR6:2 = Reserved
MR1:0 = Mode Select bits
*/
#define OPERATING_MODE_CONT_MEAS 0	//Continuous measurement mode
#define OPERATING_MODE_SING_MEAS 1	//Single-measurement mode
#define OPERATING_MODE_IDLE		 2	//Idle mode.

/*
Status register SR = Read-Only status register

*/
#define HMC5883L_LOCK (1 << 1)	//Data register output lock
#define HMC5883L_RDY  (1 << 0)	//Ready Bit

//Struct for magnetometer data:
typedef struct 
{
    unsigned int X_MSB;
    unsigned int X_LSB;
    unsigned int Y_MSB;
    unsigned int Y_LSB;
    unsigned int Z_MSB;
    unsigned int Z_LSB;
} HMC5883L_DATA;


//Configuration functions:
void setup_HMC5883L_CRA();
void setup_HMC5883L_CRB();
void setup_HMC5883L_MR();
HMC5883L_DATA read_batch_of_data();
int read_CRA();
int read_CRB();
int read_MR();

#endif