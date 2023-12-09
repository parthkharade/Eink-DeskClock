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
#define I2C1_MUXPOS		4U
#define TIM4_CC1_MUXPOS 2U
void init_mux(){

	//SPI PINS PA5/CLK PA7/DO. The interface does not require a DI pin. Chip Select is implemented as a GPIO
	GPIOA->MODER	|= (AF_MODE<<GPIO_MODER_MODER5_Pos)| (AF_MODE<<GPIO_MODER_MODER7_Pos);
	GPIOA->AFR[0] 	|= (SPI1_MUXPOS<<GPIO_AFRL_AFSEL5_Pos)|(SPI1_MUXPOS<<GPIO_AFRL_AFSEL7_Pos);

	//I2C PINS PB6/SCL and PB7/SDA

	GPIOB->MODER	|= (AF_MODE<<GPIO_MODER_MODER6_Pos)|(AF_MODE<<GPIO_MODER_MODER7_Pos);
	GPIOB->AFR[0] 	|= (I2C1_MUXPOS<<GPIO_AFRL_AFSEL6_Pos)|(I2C1_MUXPOS<<GPIO_AFRL_AFSEL7_Pos);

	// TIM4 Compare Channel 1 mapped to PD12 which will serve as a ninput for PD12
	GPIOD->MODER |= (AF_MODE<<GPIO_MODER_MODE12_Pos);
	GPIOD->AFR[1] 	|= (TIM4_CC1_MUXPOS<<GPIO_AFRH_AFSEL12_Pos);
}

