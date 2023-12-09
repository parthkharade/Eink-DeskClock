/*
 * timer.c
 *
 *  Created on: Oct 6, 2023
 *      Author: Parth
 */
#include "timer.h"
#include "stm32f411xe.h"
#include "stdint.h"
uint8_t timer4_status = 0;
void timer4_init(){
		// Enable RCC Clock for Timer2

	TIM4->CR1 |= TIM_CR1_ARPE;

	TIM4->PSC = TIM4_100K_PSC; 				//Pre-scalar value. Sets clock to 100KHz

	TIM4->ARR = TIM4_ARR_VAL;				//Generates interuupts at 1000Hz

	//Compare Mode Configuration
	TIM4->CCMR1 |= (0b110<<TIM_CCMR1_OC1M_Pos)|(TIM_CCMR1_OC1PE);
	TIM4->CCR1 = 60;
	TIM4->EGR |= TIM_EGR_UG;				//Generate an Update Event
	TIM4->CCER	|= (0b1<<TIM_CCER_CC1E_Pos);

}

void timer5_init(){

//	TIM5->CR1 |= TIM_CR1_ARPE;

	TIM5->PSC = 47999; 				//Pre-scalar value. Sets clock to 100KHz

	TIM5->ARR = 1000;				//Generates interuupts at 1000Hz
	TIM5->CNT = 0;
	TIM5->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM5_IRQn);

}
void start_timer(TIM_TypeDef * TIM){
	TIM->CR1 |= TIM_CR1_CEN;				//Enable Counter
}

void stop_timer(TIM_TypeDef * TIM){
	TIM->CR1 &= !TIM_CR1_CEN;				//Disable Counter
}
void TIM5_IRQHandler(){
	if(timer4_status){
		stop_timer(TIM4);
		timer4_status = 0;
	}
	else
	{
		start_timer(TIM4);
		timer4_status = 1;
	}
	TIM5->SR &= ~ TIM_SR_UIF;
	NVIC_ClearPendingIRQ(TIM5_IRQn);

}
