#include "defines.h"
#include "i2c.h"


rpi_i2c_controller * IC2_controller = (rpi_i2c_controller*) BSC1_BASE;

void I2C_set_slave_addr(unsigned int addr)
{
	IC2_controller->A = addr;
}

void I2C_start_read_transfer()
{
	IC2_controller->C |= (I2C_C_I2CEN|I2C_C_ST|I2C_C_READ);
}

void I2C_start_write_transfer()
{
	//Clear READ
	IC2_controller->C &= (0xFFFFFFFE);
	//Start transfer
	IC2_controller->C |= (I2C_C_I2CEN|I2C_C_ST);
}

void I2C_clear_FIFO()
{
	IC2_controller->C |= I2C_C_CLEAR;
}

void I2C_clear_S()
{
	IC2_controller->S = I2C_S_CLKT | I2C_S_ERR | I2C_S_DONE;
}

void I2C_write_FIFO(unsigned int * data, unsigned int bytes)
{
	unsigned int i = 0;
	//i<16 because the FIFO can only fit 16 bytes of data
	for(i=0; (i<bytes) && (i<16); i++)
	{
		IC2_controller->FIFO = (*(data+i) & 0xFF);
		//uprintf("Writing %x\n",*(data+i) & 0xFF);
	}
}

int I2C_read_FIFO()
{
	return (IC2_controller->FIFO & 0xFF); // Mask output with 00000000000000000000000011111111
}

void I2C_set_data_length(unsigned int dlen)
{
	//max value = 65535
	if(dlen > 65535)
	{
		IC2_controller->DLEN = 65535;
	}
	else
	{
		IC2_controller->DLEN = dlen;
	}		
}

unsigned int I2C_get_DONE()
{
	return (IC2_controller->S & I2C_S_DONE);
}

/** 
@brief Function to write data on the I2C-bus
bytes = the number of data bytes to write
slave_addr = address of the I2C-slave to write to
data = pointer to array of integers that form the data to transmit
*/
void I2C_write(unsigned int bytes, unsigned int slave_addr, unsigned int * data)
{
	//Reset I2C state
	I2C_clear_FIFO();
	I2C_clear_S();
	
	//Set the address of the slave to write to
	I2C_set_slave_addr(slave_addr);
	
	//Fill the FIFO with the data to write
	I2C_write_FIFO(data, bytes);
	
	//Set the data length register:
	I2C_set_data_length(bytes);
	
	//Start the write transfer
	I2C_start_write_transfer();
	
	while(!(IC2_controller->S & I2C_S_DONE))
	{
		//If the FIFO is empty, but not all data is transmitted,
		//fill up the FIFO again
		if(IC2_controller->S & I2C_S_TXW)
		{
			//Lower the number of bytes to be transmitted
			bytes -= 16;
			//Increase the pointer value
			data += 16;
			//Fill FIFO again
			I2C_write_FIFO(data,bytes);
		}
		else if(IC2_controller->S & I2C_S_ERR)
		{
			//Received NACK, end transmission
			break;
		}
	}
}


/** 
@brief Function to write data on the I2C-bus
bytes = the number of data bytes to read
slave_addr = address of the I2C-slave to write to
reg_addr = address of the register on the slave that needs to be read
data = pointer to array of integers that form the data to receive
*/
void i2c_read_register(unsigned int bytes, unsigned int slave_addr, unsigned int reg_addr, unsigned int * data)
{
	//Reset I2C state
	I2C_clear_FIFO();
	I2C_clear_S();
	
	//Set the address of the slave to write to
	I2C_set_slave_addr(slave_addr);
	
	//Set the data length register: We first transmit one byte as the target register
	I2C_set_data_length(1);
	
	//Fill the FIFO with the data to write
	I2C_write_FIFO(&reg_addr, 1);
	
	//Start the write transfer:
	I2C_start_write_transfer();
	
	//Wait until the transfer has started
	while(!(IC2_controller->S & I2C_S_TA))
	{
		if(IC2_controller->S & I2C_S_DONE)
		{
			//We somehow missed the transfer
			break;
		}
	}
	
	//Now receive the actual data
	I2C_set_data_length(bytes);
	I2C_start_read_transfer();
	
	//Wait for the read to be done
	while(!(IC2_controller->S & I2C_S_DONE))
	{
		//If the FIFO is full, but not all data is transmitted,
		//empty the FIFO
		if(IC2_controller->S & I2C_S_RXR)
		{
			unsigned int i = 0;
			for(i=0;i<16;i++)
			{
				*data = I2C_read_FIFO();
				data++;
				bytes--;
			}
		}
		else if(IC2_controller->S & I2C_S_ERR)
		{
			//Received NACK, end transmission
			break;
		}
	}
	
	//Now read all other data remaining in the FIFO
	unsigned int i =0;
	for(i=0; i<bytes;i++)
	{
		*data = I2C_read_FIFO();
		data++;
	}
}

void I2C_handle_DONE()
{
	//If we were reading data
	if(IC2_controller->C & I2C_C_READ)
	{
		//Empty the FIFO
		//According to the datasheet, after a transmission,
		//when DONE is set 0 again,
		//DLEN = the value last written
		//By then taking the modulo 16 of this value,
		//the remaining number of bytes in the FIFO can be found.
		
		//Reset DONE:
		IC2_controller->S |= I2C_S_DONE;
		
		//Calculate the number of bytes to be read
		unsigned int len = IC2_controller->DLEN % 16;
		
		//Read these bytes
		unsigned int i =0;
		for(i=0;i<len;i++)
		{
			*data_buffer = I2C_read_FIFO();
			data_buffer++;
		}
		
		
	}
	//Otherwise, we were writing data
	else
	{
		//Do nothing, write was succesfull ?
	}
}

void I2C_handle_RXR()
{
	//The FIFO needs to be read:
	
}

void I2C_handle_TXW()
{
	
}

void I2C_setup()
{
	
}

unsigned int I2C_get_TXW(){return (IC2_controller->S >> 2) & 1;}
unsigned int I2C_get_RXR(){return (IC2_controller->S >> 3) & 1;}
unsigned int I2C_get_TXD(){return (IC2_controller->S >> 4) & 1;}
unsigned int I2C_get_RXD(){return (IC2_controller->S >> 5) & 1;}
unsigned int I2C_get_TXE(){return (IC2_controller->S >> 6) & 1;}
unsigned int I2C_get_RXF(){return (IC2_controller->S >> 7) & 1;}


void set_I2C_clk_div_100kHz()
{
	IC2_controller->DIV = 1500; //Results in SCL = 100kHz.
}

void set_I2C_clk_div(int clk_freq)
{
	IC2_controller->DIV = 150000000 / clk_freq; //Results in DIV = 150MHz (nominal freq) /  clk_freq.
}

void disable_I2C_clock_stretch_timeout()
{
	//From datasheet p34:
	//"Writing 0x0 to TOUT (this register) will result in the Clock
	//Stretch Timeout being disabled."
	IC2_controller->CLKT = 0;
}


void set_I2C_data_delay()
{
	//Clear previous values:
	IC2_controller->DEL = 0;
	//Set Falling Edge Delay: 11111111111111110000000000000000
	IC2_controller->DEL |= 0;
	//Set Rising Edge Delay:  00000000000000001111111111111111
	IC2_controller->DEL |= 0;
}