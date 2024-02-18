/*
 * clocks.c
 *
 *  Created on: Dec 20, 2023
 *      Author: Parth
 */

#include "clocks.h"
void init_clocks(){

		RCC->CR	&= ~(RCC_CR_PLLON);
		RCC->CFGR |= (0b11<< RCC_CFGR_MCO1_Pos);
		FLASH->ACR = (1<<8) | (1<<9)| (1<<10)| (5<<0);
		RCC->PLLCFGR = 0;
		RCC->PLLCFGR |= (8<<RCC_PLLCFGR_PLLQ_Pos)|(8<<RCC_PLLCFGR_PLLM_Pos)|(192<<RCC_PLLCFGR_PLLN_Pos)|(1<<RCC_PLLCFGR_PLLP_Pos);
		RCC->CR |= RCC_CR_HSION;
		while(!( RCC->CR & RCC_CR_HSIRDY));
		RCC->CFGR |= (0b100<<RCC_CFGR_PPRE1_Pos)|(0b000<<RCC_CFGR_PPRE2_Pos)|(0b0000<<RCC_CFGR_HPRE_Pos);
		RCC->CR |= RCC_CR_PLLON;
		while(!( RCC->CR & RCC_CR_PLLRDY));
		RCC->CFGR |= (0b10<<RCC_CFGR_SW_Pos);
		while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
}
void enable_module_clocks(){
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN); 	// GPIO A
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN); 	//GPIO B
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 	// SPI1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; 	// I2C1
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 	// GPIOD
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;		// TIMER4;
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;		// TIMER4;
}
