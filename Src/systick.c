/*
 * systick.c
 *
 *  Created on: Oct 25, 2023
 *      Author: Parth
 */

#include "stm32f411xe.h"
#include "systick.h"


volatile sys_time_t sys_time = {.mins = 0, .ms =0};
void init_systick(){
	 SysTick->CTRL	|= 	SysTick_CTRL_TICKINT_Msk; // Set clock source to internal clock and enable sys-tick interrupt.
	 SysTick->LOAD	= 	SYSTICK_CLK*TICK_TIME_MS/1000; // Tick of 1ms.
}
void stop_systick(){
	SysTick->CTRL 	&= 	~(SysTick_CTRL_ENABLE_Msk);
	SysTick->VAL 	= 0;
}
void start_systick(){
	SysTick->CTRL 	|= 	SysTick_CTRL_ENABLE_Msk;
}
void SysTick_Handler(){
	sys_time.ms++;
}
sys_time_t get_time(){
	return sys_time;
}
void delay_ms(uint32_t delay){
	sys_time_t sys_time_curr = get_time();
	uint32_t end_ms = (sys_time_curr.ms + delay)>60000?(sys_time_curr.ms+delay-60000) :(sys_time_curr.ms+delay);
	while(get_time().ms < end_ms);
}
