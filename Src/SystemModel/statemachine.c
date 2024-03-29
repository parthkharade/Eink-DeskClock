/*
 * statemachine.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */


#include "statemachine.h"
#include "clockface.h"
#include "alarms.h"
#include "timeanddate.h"
typedef void(*clockstate_callback)();


extern uint8_t update_display;

typedef struct{
	clock_state_t curr_state;
	clock_state_t next_state[4]; // First entry corresponds to S1 being pressed  second is S2 and so on
	clockstate_callback callback_func[4]; // Similar to the next state field.
}state_table_entry_t;



/**
 * {S1,S2,S3,S4}
 */
state_table_entry_t state_tbl[] = {
	{IDLE , 				{IDLE, 					ALARM_CONFIG_SELECT,  	TIME_CONFIG_UPD_MIN0,  	DATE_CONFIG_UPD_DATE},	 {empty_function,empty_function,empty_function,empty_function}},

	{ALARM_CONFIG_SELECT, 	{IDLE,  				ALARM_CONFIG_UPD_MIN0,  ALARM_CONFIG_SELECT, 	 ALARM_CONFIG_SELECT},	 {empty_function,empty_function,alarm_toggle,alarm_inc_index}},
	{ALARM_CONFIG_UPD_MIN0, {ALARM_CONFIG_SELECT,  	ALARM_CONFIG_UPD_MIN1,  ALARM_CONFIG_UPD_MIN0, 	 ALARM_CONFIG_UPD_MIN0}, {empty_function,empty_function,alarm_dec_min0,alarm_inc_min0}},
	{ALARM_CONFIG_UPD_MIN1, {ALARM_CONFIG_SELECT,  	ALARM_CONFIG_UPD_HRS0,  ALARM_CONFIG_UPD_MIN1, 	 ALARM_CONFIG_UPD_MIN1}, {empty_function,empty_function,alarm_dec_min1,alarm_inc_min1}},
	{ALARM_CONFIG_UPD_HRS0, {ALARM_CONFIG_SELECT,  	ALARM_CONFIG_UPD_HRS1,  ALARM_CONFIG_UPD_HRS0, 	 ALARM_CONFIG_UPD_HRS0}, {empty_function,empty_function,alarm_dec_hrs0,alarm_inc_hrs0}},
	{ALARM_CONFIG_UPD_HRS1, {ALARM_CONFIG_SELECT,  	ALARM_CONFIG_UPD_MIN0,  ALARM_CONFIG_UPD_HRS1, 	 ALARM_CONFIG_UPD_HRS1}, {empty_function,empty_function,alarm_dec_hrs1,alarm_inc_hrs1}},

	{TIME_CONFIG_UPD_MIN0, {IDLE,  					IDLE,  					TIME_CONFIG_UPD_MIN1, 	 TIME_CONFIG_UPD_MIN0}, {update_time,set_time_mcp7490,empty_function,time_inc_min0}},
	{TIME_CONFIG_UPD_MIN1, {IDLE,  					IDLE, 				 	TIME_CONFIG_UPD_HRS0, 	 TIME_CONFIG_UPD_MIN1}, {update_time,set_time_mcp7490,empty_function,time_inc_min1}},
	{TIME_CONFIG_UPD_HRS0, {IDLE,  					IDLE,  					TIME_CONFIG_UPD_HRS1, 	 TIME_CONFIG_UPD_HRS0}, {update_time,set_time_mcp7490,empty_function,time_inc_hrs0}},
	{TIME_CONFIG_UPD_HRS1, {IDLE,  					IDLE,  					TIME_CONFIG_UPD_MIN0, 	 TIME_CONFIG_UPD_HRS1}, {update_time,set_time_mcp7490,empty_function,time_inc_hrs1}},
};



clock_state_t curr_state = IDLE;
void process_event(uint8_t event){
	//calls appropriate callback according to current state and event.

	// event 1 is S1 event 2 is s2 and so on.
	if (event >= 1) {
		state_tbl[curr_state].callback_func[event-1]();
		curr_state = state_tbl[curr_state].next_state[event-1];
		update_clockface = 1;
	}
	// Event zero is when S1 is pressed when an alarm is ringing. This action mutes the alarm.
	else{
		mute_alarm();
	}
	//changes state according to current state and event.

}

void empty_function(){

}


