/*
 * statemachine.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "stdint.h"
#include "alarms.h"
typedef enum{
	IDLE,

	ALARM_CONFIG_SELECT,
	ALARM_CONFIG_UPD_MIN0,
	ALARM_CONFIG_UPD_MIN1,
	ALARM_CONFIG_UPD_HRS0,
	ALARM_CONFIG_UPD_HRS1,

	TIME_CONFIG_UPD_MIN0,
	TIME_CONFIG_UPD_MIN1,
	TIME_CONFIG_UPD_HRS0,
	TIME_CONFIG_UPD_HRS1,

	DATE_CONFIG_UPD_DATE,
	DATE_CONFIG_UPD_MONTH,
	DATE_CONFIG_UPD_YEAR,
	DATE_CONFIG_UPD_DAY,

}clock_state_t;

extern clock_state_t curr_state;
void empty_function();



void time_inc_min0();
void time_dec_min0();
void time_inc_min1();
void time_dec_min1();

void time_inc_hrs0();
void time_dec_hrs0();
void time_inc_hrs1();
void time_dec_hrs1();

void process_event(uint8_t event);
#endif /* STATEMACHINE_H_ */

