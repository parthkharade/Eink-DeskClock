/*
 * gpio.c
 *
 *  Created on: Oct 6, 2023
 *      Author: Parth
 */
#include "stm32f411xe.h"
#include "gpio.h"
#include "stdint.h"
#include "systick.h"
void init_gpio(){

	// Set D/C Pin as output
	GPIOA->MODER |= (1<<GPIO_MODER_MODE0_Pos);
	// Set CS High
	GPIOA->BSRR |= GPIO_BSRR_BS0;

	// Set CS Pin as output
	GPIOA->MODER |= (1<<GPIO_MODER_MODE1_Pos);
	// Set CS High
	GPIOA->BSRR |= GPIO_BSRR_BS1;

	// Set RST Pin as output
	GPIOA->MODER |= (1<<GPIO_MODER_MODE2_Pos);
	// Set RST High
	GPIOA->BSRR |= GPIO_BSRR_BS2;

	// Set BSY Pin as input
	GPIOA->MODER |= (0<<GPIO_MODER_MODE3_Pos);

}
