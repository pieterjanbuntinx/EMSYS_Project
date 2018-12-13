#include "HMC5883L.h"
#include "rpi-uart.h"
#include "rpi-system-timer.h"
//#include "i2c.c"


/*
Example power-up initialization
Steps to enable magnetometer readings:
1) Write CRA -> 8 average measurements, 15Hz and normal measurement:
	send: 0x3C 0x00 0x70
		0x3C = Slave address for write operations
		0x00 = Configuration Register A address
		0x70 = 0111 0000 => Number of samples is 11, Data Output Rate = 15
2) Set the gain to a known level
	send: 0x3C 0x01 0xA0
		0x3C = Slave address for write operations
		0x01 = Configuration Register B address
		0xA0 = MAGGAIN_4_7
3) Change the operation mode
	send: 0x3C 0x02 0x00
		0x3C = Slave address for write operations
		0x02 = Address of operation Mode Register MR
		0x00 = Continuous Measurement mode
4) Either wait 6ms or monitor DRDY interrupt pin
5) Loop:
	send: 0x3D 0x06
		0x3D = Slave address for read operations
		0x06 = Read the next 6 bytes
	send: 0x3C 0x03
		Point to first data register 0x03
	Wait 67ms (15Hz rate) or for DRDY interrupt pin
	End_loop

Why does this loop work:
	The address pointer is automatically incremented after each succesful READ operation
	To read another address, you first need to set the address pointer to that addres with a write operation:
		0x3C 0x0?
	It must be noted that the WRITE operations do NOT increment the address pointer
	
*/

void setup_HMC5883L()
{	
	//We first want to set up the Configuration Register A:
	setup_HMC5883L_CRA();
	
	//Next we want to set up the Configuration Register B:
	setup_HMC5883L_CRB();

	//Finally, correctly setup the Operation Mode
	setup_HMC5883L_MR();
	
	//Then, wait 6ms (TODO: DRDY INT PIN)
	volatile unsigned int tim;
	for(tim = 0; tim<10000;tim++);
	
	int CRA = read_CRA();
	uprintf("CRA = %d\n",CRA);
	
	for(tim = 0; tim<10000;tim++);
	
	int CRB = read_CRB();
	uprintf("CRB = %d\n",CRB);
	
	for(tim = 0; tim<10000;tim++);
	
	int MR = read_MR();
	uprintf("MR  = %d\n",MR);
	
	while(1)
	{
		//for(tim = 0; tim<1000000;tim++);
		delay_ms(67);
		HMC5883L_DATA data = read_batch_of_data();
	
		signed int X = (data.X_MSB << 8) | data.X_LSB;
		if(X > 32768) X -= 65535; //00000000000000001000000000000000 signifies a negative number in this implementation
		signed int Y = (data.Y_MSB << 8) | data.Y_LSB;
		if(Y > 32768) Y -= 65535;
		signed int Z = (data.Z_MSB << 8) | data.Z_LSB;
		if(Z > 32768) Z -= 65535;
		
		uprintf("Data = (%d,%d,%d)\n",X,Y,Z);
	}
	
}


void setup_HMC5883L_CRA()
{
	unsigned int data[2];
	data[0] = HMC5883L_REGISTER_MAG_CRA_REG_M;
	data[1] = NUM_SAMPLES_8|DOR_15|MM_NORMAL;
		
	I2C_write(2, HMC5883L_SLAVE_ADDR, data);
}

void setup_HMC5883L_CRB()
{
	unsigned int data[2];
	data[0] = HMC5883L_REGISTER_MAG_CRB_REG_M;
	data[1] = MAGGAIN_1_9;
		
	I2C_write(2, HMC5883L_SLAVE_ADDR, data);
}

void setup_HMC5883L_MR()
{
	unsigned int data[2];
	data[0] = HMC5883L_REGISTER_MAG_MR_REG_M;
	data[1] = OPERATING_MODE_CONT_MEAS;
	I2C_write(2, HMC5883L_SLAVE_ADDR, data);
}

int read_CRA()
{	
	int data[0];
	i2c_read_register(1, HMC5883L_SLAVE_ADDR, HMC5883L_REGISTER_MAG_CRA_REG_M, data);
	return data[0];
}

int read_CRB()
{
	int data[0];
	i2c_read_register(1, HMC5883L_SLAVE_ADDR, HMC5883L_REGISTER_MAG_CRB_REG_M, data);
	return data[0];
}

int read_MR()
{
	int data[0];
	i2c_read_register(1, HMC5883L_SLAVE_ADDR, HMC5883L_REGISTER_MAG_MR_REG_M, data);
	return data[0];
}


HMC5883L_DATA read_batch_of_data()
{
	HMC5883L_DATA data_batch;
	unsigned int buffer [6];
	unsigned int i = 0;
	for(i=0;i<6;i++)
	{
		i2c_read_register(1, HMC5883L_SLAVE_ADDR, HMC5883L_REGISTER_MAG_OUT_X_H_M + i, buffer+i);
	}
	
	data_batch.X_MSB = buffer[0];
	data_batch.X_LSB = buffer[1];
	data_batch.Z_MSB = buffer[2];
	data_batch.Z_LSB = buffer[3];
	data_batch.Y_MSB = buffer[4];
	data_batch.Y_LSB = buffer[5];
	return data_batch;
}
