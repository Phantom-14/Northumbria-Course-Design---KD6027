//===============================
//Author: Yutong Zhu
//Data: 10/1/2022
//Descibtion: GPIO driver source file
//Student Number: 18047451
//E-mail: w18047451@northumbria.ac.uk
//===============================
#ifndef _I2C_H
#define _I2C_H

#define I2C_DisableAck()       I2C0_C1 |= I2C_C1_TXAK_MASK
#define I2C_EnableAck()        I2C0_C1 &= ~I2C_C1_TXAK_MASK
#define I2C_RepeatedStart()    I2C0_C1 |= I2C_C1_RSTA_MASK
#define I2C_EnterRxMode()      I2C0_C1 &= ~I2C_C1_TX_MASK

#define I2C_Start()            I2C0_C1 |= I2C_C1_TX_MASK;\
                               I2C0_C1 |= I2C_C1_MST_MASK

#define I2C_Stop()             I2C0_C1 &= ~I2C_C1_MST_MASK;\
                               I2C0_C1 &= ~I2C_C1_TX_MASK

#define I2C_Wait()             while((I2C0_S & I2C_S_IICIF_MASK)==0) {} \
                               I2C0_S |= I2C_S_IICIF_MASK;

//error codes	
#define ERR_NONE 			0
#define ERR_NO_ACK 		0x01
#define ERR_ARB_LOST 	0x02
#define ERR_BUS_BUSY 	0x03
	
//===========================================
//Function name: i2c_init
//Describtion: initilize I2C0->PTE24 PTE25
//===========================================
void i2c_init(void);
	
//===========================================
//Function name: 	i2c_signal
//Describtion: 		send start or end signal;
//Parameters:			's'(start)->start signal; 'o'(over)->over signal;
//								'r'(restart)->restart signal;
//===========================================
void i2c_start(void);   	

//===========================================
//Function name: 	i2c_WrByte
//Describtion: 		send a byte to slave
//Parameters:			SlavAddr->7 bits address of slave
//								RegAddr	->the register address to write
//								Data		->data sent
//Function return:0	-> None Error:send successfully
//								1 -> No Ack:Slave not response
//===========================================
int i2c_WrByte(unsigned char SlaveAddr, unsigned char RegAddr, char Data);

//===========================================
//Function name: 	i2c_RdByte
//Describtion: 		read a byte from slave
//Parameters:			SlavAddr->7 bits address of slave
//								RegAddr	->the register address to write
//===========================================
unsigned char i2c_RdByte(unsigned char SlaveAddr, unsigned char RegAddr);

//===========================================
//Function name: i2c_RdMultiBytes
//Describtion: Read n bytes data from slave to r
//===========================================
void i2c_RdMultiBytes(unsigned char SlaveAddr, unsigned char RegAddr, unsigned char n, unsigned char *r);

//===========================================
//Function name: Pause
//Describtion: 	execute very times of nop
//Parameters:		nop times
//===========================================
void Pause(int number);
#endif
