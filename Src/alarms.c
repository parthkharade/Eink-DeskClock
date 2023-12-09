/*
 * alarms.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */
#include "alarms.h"
#include "mcp7940.h"
#include "timer.h"
uint8_t alarm_index;
uint8_t alarm_ring_index;
alarm_t alarm_table[]={
		{0x23,0x02,0,1,0},
		{0x23,0x03,0,1,0},
		{0x23,0x04,0,1,0},
		{0x23,0x05,0,1,0}
};

void system_enable_alarms(){
	for(int i=0;i<4;i++){
		alarm_table[i].sys_alarm_enb = 1;
	}
}
void check_alarm_match(){
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (mcp_curr_time.hrs == alarm_table[i].alarm_hrs
				&& mcp_curr_time.min == alarm_table[i].alarm_min) {
			alarm_ring_index = i;
			break;
		}
	}
	if (i < 4) {
		if (alarm_table[alarm_ring_index].usr_alarm_enb
				&& alarm_table[alarm_ring_index].sys_alarm_enb) {
			sound_alarm();
		}
	}
}

void sound_alarm(){
	if (!alarm_table[alarm_ring_index].is_alarm_ringing) {
		alarm_table[alarm_ring_index].is_alarm_ringing = 1;
		start_timer(TIM5);
		start_timer(TIM4);
	}
}

void mute_alarm(){
	alarm_table[alarm_ring_index].is_alarm_ringing = 0;
	alarm_table[alarm_ring_index].sys_alarm_enb = 0;
	stop_timer(TIM5);
	stop_timer(TIM4);
}
alarm_t *get_alarms(){
	return alarm_table;
}
uint8_t is_alarm_ringing(){
	uint8_t alarm_ring_status = 0;
	for(int i=0;i <4;i++){
		alarm_ring_status|=alarm_table[i].is_alarm_ringing;
	}
	return alarm_ring_status;
}
void alarm_toggle(){
	if(alarm_table[alarm_index].usr_alarm_enb){
		alarm_table[alarm_index].usr_alarm_enb = 0;
	}
	else{
		alarm_table[alarm_index].usr_alarm_enb = 1;
	}
}
void alarm_inc_index(){
	alarm_index+=1;
	alarm_index%=4;
}

void alarm_inc_min0(){
	alarm_table[alarm_index].alarm_min ++;
	if(((alarm_table[alarm_index].alarm_min) & 0x0F) == 0x0A)
		alarm_table[alarm_index].alarm_min &= 0xF0;
}
void alarm_dec_min0(){
	if(((alarm_table[alarm_index].alarm_min) & 0x0F) == 0x00)
		alarm_table[alarm_index].alarm_min |= 0x09;
	else
		alarm_table[alarm_index].alarm_min --;
}
void alarm_inc_min1(){
	alarm_table[alarm_index].alarm_min +=16;
	if(((alarm_table[alarm_index].alarm_min) & 0xF0) == 0x60)
		alarm_table[alarm_index].alarm_min &= 0x0F;
}
void alarm_dec_min1(){
	if(((alarm_table[alarm_index].alarm_min) & 0xF0) == 0x00)
		alarm_table[alarm_index].alarm_min |= 0x50;
	else
		alarm_table[alarm_index].alarm_min -=16;
}

void alarm_inc_hrs0(){
	alarm_table[alarm_index].alarm_hrs ++;
	if(((alarm_table[alarm_index].alarm_hrs) & 0x0F) == 0x0A)
		alarm_table[alarm_index].alarm_hrs &= 0xF0;
}
void alarm_dec_hrs0(){
	if(((alarm_table[alarm_index].alarm_hrs) & 0x0F) == 0x00)
		alarm_table[alarm_index].alarm_hrs |= 0x09;
	else
		alarm_table[alarm_index].alarm_hrs --;
}
void alarm_inc_hrs1(){
	alarm_table[alarm_index].alarm_hrs +=16;
	if(((alarm_table[alarm_index].alarm_hrs) & 0xF0) == 0x30)
		alarm_table[alarm_index].alarm_hrs &= 0x0F;
}
void alarm_dec_hrs1(){
	if(((alarm_table[alarm_index].alarm_hrs) & 0xF0) == 0x00)
		alarm_table[alarm_index].alarm_hrs |= 0x20;
	else
		alarm_table[alarm_index].alarm_hrs -=16;
}
