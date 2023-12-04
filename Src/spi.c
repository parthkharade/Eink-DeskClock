/*
 * spi.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Parth
 */

#include "spi.h"
void init_spi1(){
	// Enable Peripheral, Set Clock Pre_scalar to 4 and set in master mode.
	SPI1->CR1 |= (1<<SPI_CR1_BR_Pos);
	SPI1->CR1 |= SPI_CR1_SSM|SPI_CR1_SSI;
	SPI1->CR1 |= SPI_CR1_SPE|SPI_CR1_MSTR;
	// CPOL and CPHA are 0.
}

void tx_byte(uint8_t byte){
	while(!(SPI1->SR & SPI_SR_TXE));
	SPI1->DR = byte;
}

uint8_t rx_byte(){
	uint8_t byte;
	while(! (SPI1->SR & SPI_SR_RXNE));
	byte = SPI1->DR;
	return byte;
}
