/*
 * alarms.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */
#include "alarms.h"

uint8_t alarm_index;
alarm_t alarm_table[]={
		{0x17,0x00,0},
		{0x18,0x00,0},
		{0x19,0x00,0},
		{0x20,0x00,0}
};

uint8_t check_alarm_match(){

}
alarm_t *get_alarms(){
	return alarm_table;
}

void alarm_toggle(){
	if(alarm_table[alarm_index].alarm_enb){
		alarm_table[alarm_index].alarm_enb = 0;
	}
	else{
		alarm_table[alarm_index].alarm_enb = 1;
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
