/*
 * spi.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Parth
 */

#ifndef SPI_H_
#define SPI_H_
#include "stm32f411xe.h"

#define SET_CS GPIOA->BSRR |= GPIO_BSRR_BS1
#define CLR_CS GPIOA->BSRR |= GPIO_BSRR_BR1

#define SPI_BUSY ((SPI1->SR) & (SPI_SR_BSY))
/**
 * @brief Initialises SPI1 in master mode to communicate at 4MHz
 */
void init_spi1();

/**
 * @brief Sends a byte on the SPI channel 
 * 
 * @param byte 
 */
void tx_byte(uint8_t byte);


/**
 * @brief Reads a byte from the SPI Channel 
 * 
 * @return uint8_t 
 */
uint8_t rx_byte();
#endif /* SPI_H_ */
