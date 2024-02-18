/*
 * statemachine.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "stdint.h"

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

/**
 * @brief An empty callback function when a state change is required without any action 
 * 
 */
void empty_function();

/**
 * @brief Process the event that has occured by executing the required state change and the callback function. 
 * 
 * @param event 
 */
void process_event(uint8_t event);
#endif /* STATEMACHINE_H_ */

