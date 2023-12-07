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
void init_systick();
void start_systick();
sys_time_t get_time();
void delay_ms(uint32_t delay);
#endif /* SYSTICK_H_ */
