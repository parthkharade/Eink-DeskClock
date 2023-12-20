/*
 * timeanddate.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */
#include "timeanddate.h"
#include "mcp7940.h"
#include "alarms.h"
#include "statemachine.h"
rtc_time_t last_read_time;
void update_time(){
	get_time_mcp7490();
	if(!(curr_state >= TIME_CONFIG_UPD_MIN0 && curr_state <= TIME_CONFIG_UPD_HRS1)){
		mcp_config_time.sec 	=	0;
		mcp_config_time.min 	=	mcp_curr_time.min;
		mcp_config_time.hrs 	=	mcp_curr_time.hrs;
		mcp_config_time.day  	=	mcp_curr_time.day;
		mcp_config_time.date 	=	mcp_curr_time.date;
		mcp_config_time.month 	=	mcp_curr_time.month;
		mcp_config_time.year	=	mcp_curr_time.year;
	}
}
uint8_t check_time_diff(){
	if(mcp_curr_time.min!=last_read_time.min){
		last_read_time.min = mcp_curr_time.min;
		system_enable_alarms();
		return 1;
	}
	else{
		return 0;
	}
}

void time_inc_min0(){
	mcp_config_time.min ++;
	if(((mcp_config_time.min) & 0x0F) == 0x0A)
		mcp_config_time.min &= 0xF0;
}
void time_inc_min1(){
	mcp_config_time.min +=16;
	if(((mcp_config_time.min) & 0xF0) == 0x60)
		mcp_config_time.min &= 0x0F;
}
void time_inc_hrs0(){
	mcp_config_time.hrs ++;
	if((((mcp_config_time.hrs) & 0xF0) == 0x20) && (((mcp_config_time.hrs) & 0x0F) == 0x04)){
		mcp_config_time.hrs &= 0xF0;
	}
	else if(((mcp_config_time.hrs) & 0x0F) == 0x0A){
		mcp_config_time.hrs &= 0xF0;
	}
}

void time_inc_hrs1(){
	mcp_config_time.hrs +=16;
	if( ((mcp_config_time.hrs & 0x0F) >= 0x04) && ((mcp_config_time.hrs & 0xF0) == 0x20))
		mcp_config_time.hrs &= 0x0F;
	else if((mcp_config_time.hrs & 0xF0) == 0x30){
		mcp_config_time.hrs &= 0x0F;
	}
}
