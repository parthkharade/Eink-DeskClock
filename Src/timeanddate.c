/*
 * timeanddate.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */
#include "timeanddate.h"
#include "mcp7940.h"
#include "alarms.h"
rtc_time_t last_read_time;
void update_time(){
	get_time_mcp7490();
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
