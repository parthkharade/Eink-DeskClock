/*
 * timer.h
 *
 *  Created on: Oct 6, 2023
 *      Author: Parth
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f411xe.h"
#define TIM4_NVIC_OFF 	30U
#define TIM4_100K_PSC	159U
#define TIM4_ARR_VAL	100U

#define TIM2_NVIC_OFF 	28U
#define TIM2_100K_PSC	159U
#define TIM2_ARR_VAL	100U

// 100000/100 = 1000Hz

/**
 * @brief 		: 	This function intialises the Timer 4 for LED PWM Signal.
 * @param[in]	: 	None
 * @return 		:	None
 * */
void timer4_init();
void timer5_init();
/**
 * @brief 		: 	Start the timer.
 * @param[in]	: 	None
 * @return 		:	None
 * */
void start_timer(TIM_TypeDef * TIM);

/**
 * @brief 		: 	Stop the timer.
 * @param[in]	: 	None
 * @return 		:	None
 * */
void stop_timer(TIM_TypeDef * TIM);

/**
 * @brief Returns the current duty cycle.
 * 
 * @return uint8_t 
 */
uint8_t get_duty();

/**
 * @brief Changes the duty cycle by step
 * 
 * @param step 
 */
void change_duty(int8_t step);
#endif /* TIMER_H_ */
