/*
 * systick.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Parth
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#define SYSTICK_CLK 	12000000
//#define SYSTICK_CLK 	2000000
#define TICK_TIME_MS	1

typedef struct{
	uint32_t mins;
	uint32_t ms;
}sys_time_t;
/**
 * @brief Initialises the systick timer. 
 * 
 */
void init_systick();

/**
 * @brief Starts the systick timer. 
 * 
 */
void start_systick();

/**
 * @brief Returns the current systime.
 * 
 * @return sys_time_t 
 */
sys_time_t get_time();

/**
 * @brief blocking delay of delay milliseconds. 
 * 
 * @param delay 
 */
void delay_ms(uint32_t delay);
#endif /* SYSTICK_H_ */
