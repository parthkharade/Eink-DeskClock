/*
 * i2c.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#include "i2c.h"
#include "stm32f411xe.h"
#include "systick.h"
uint16_t temp;
void i2c_init(){


	I2C1->CR1 |= I2C_CR1_SWRST;
	delay_ms(10);
	I2C1->CR1 &= ~I2C_CR1_SWRST;
	I2C1->CR1 |= I2C_CR1_PE;
	I2C1->CR2 |= (48<<I2C_CR2_FREQ_Pos);

	I2C1->CCR |= (240<<I2C_CCR_CCR_Pos);


}
void i2c_write_bytes(uint8_t *buff,uint8_t dev_add,uint16_t n_bytes){
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB)); // Wait for the Start Bit to be set.
	I2C1->DR = (dev_add<<1& ~(0x01));
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	temp = I2C1->SR2;
	int i=0;
	while(i<n_bytes){
		while(!(I2C1->SR1 & I2C_SR1_TXE));
		I2C1->DR = buff[i];
		i++;
	}
	while(!(I2C1->SR1 & I2C_SR1_BTF));
	I2C1->CR1 |= I2C_CR1_STOP;
}
void i2c_read_bytes(uint8_t *buff,uint8_t dev_add,uint8_t register_add,uint16_t n_bytes){
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB)); // Wait for the Start Bit to be set.
	I2C1->DR = (dev_add<<1 & ~(0x01));
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	temp = I2C1->SR2;
	while(!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = register_add;

	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB)); // Wait for the Start Bit to be set.
	I2C1->DR = (dev_add<<1 | 0x01);
	I2C1->CR1 |= (I2C_CR1_ACK);
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	temp = I2C1->SR2;
	int i=0;
	while(i<n_bytes){
		if(i == n_bytes-1){
			I2C1->CR1 &= ~(I2C_CR1_ACK);
			I2C1->CR1 |= I2C_CR1_STOP;
		}
		while(!(I2C1->SR1 & I2C_SR1_RXNE));
		buff[i] = I2C1->DR;
		i++;
	}

}

