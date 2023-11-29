/*
 * mux.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Parth
 */
#include "mux.h"
#include "stm32f411xe.h"

#define UASRT2_MUXPOS	7U
#define AF_MODE			0b10
#define SPI1_MUXPOS		5U
void init_mux(){

	//SPI PINS PA5 is CLK SPI1 PA7 is DO SPI1.
	GPIOA->MODER	|= (AF_MODE<<GPIO_MODER_MODER5_Pos)| (AF_MODE<<GPIO_MODER_MODER7_Pos);
	GPIOA->AFR[0] 	|= (SPI1_MUXPOS<<GPIO_AFRL_AFSEL5_Pos)|(SPI1_MUXPOS<<GPIO_AFRL_AFSEL7_Pos);

}

