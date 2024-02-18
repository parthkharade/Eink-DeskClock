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
uint8_t button_enable = 1;
extern uint8_t event_occurred;
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

	// PB6 (CLK) PB7(SDA) as Open Drain Outputs
	GPIOB->OTYPER |= (1<<GPIO_OTYPER_OT6_Pos)|(1<<GPIO_OTYPER_OT7_Pos);


	//PB0,PB1,PB2,PB3 Conencted to S1,S2,S3,S4 as open drain  inputs.


	GPIOB->MODER &= ~((GPIO_MODER_MODE0_Msk)|(GPIO_MODER_MODE1_Msk)|(GPIO_MODER_MODE2_Msk)|(GPIO_MODER_MODE3_Msk));

}

uint8_t get_button_status(){
	uint8_t button_raw = GPIOB->IDR&0x000F;
	if(button_raw == 0b1111){
		button_enable = 1;
	}
	if (button_enable) {
		if (button_raw == 0b1110) {
			button_enable = 0;
			event_occurred = 1;
			return 1;
		} else if (button_raw == 0b1101) {
			button_enable = 0;
			event_occurred = 1;
			return 2;
		} else if (button_raw == 0b1011) {
			button_enable = 0;
			event_occurred = 1;
			return 3;
		} else if (button_raw == 0b0111) {
			button_enable = 0;
			event_occurred = 1;
			return 4;
		} else {
			return 255;
		}
	}
	else{
		return 255;
	}
}

