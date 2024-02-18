/*
 * alarms.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */

#ifndef ALARMS_H_
#define ALARMS_H_
#include "stdint.h"
typedef struct{
	uint8_t alarm_hrs;
	uint8_t alarm_min;
	uint8_t usr_alarm_enb;
	uint8_t sys_alarm_enb;
	uint8_t is_alarm_ringing;
}alarm_t;
extern uint8_t alarm_index;
extern alarm_t alarm_table[];

/**
 * @brief Returns the address the the Alarm Table array.
 * 
 * @return alarm_t* 
 */
alarm_t *get_alarms();

/**
 * @brief Toggles the currently selected alarm 
 * 
 */
void alarm_toggle();

/**
 * @brief Changes which alarm is currently selected by incrementing the alarm_index variable. 
 * 
 */
void alarm_inc_index();

/**
 * @brief Enables the alarms at system level.
 * 
 */
void system_enable_alarms();

/**
 * @brief Checks the current time with all the alarms in the alarm table To see if there is a match. If yes then an alarm is sounded. 
 * 
 */
void check_alarm_match();
/**
 * @brief Starts timer 4 and 5 to sound the buzzer with an interval of 1s.
 * 
 */
void sound_alarm();
/**
 * @brief Mutes the alarm by stopping timer 4 and 5.
 * 
 */
void mute_alarm();
/**
 * @brief Returns the current ringing status of the buzzer.
 * 
 * @return uint8_t 
 */
uint8_t is_alarm_ringing();

/**
 * @brief Increments the XX:XY field denoted by Y for the alarm currently selected by alarm index. 
 * 
 */
void alarm_inc_min0();
/**
 * @brief Decrements the XX:XY field denoted by Y for the alarm currently selected by alarm index. 
 * 
 */

// Rest of these functions are now self explanatory.
void alarm_dec_min0();
void alarm_inc_min1();
void alarm_dec_min1();

void alarm_inc_hrs0();
void alarm_dec_hrs0();
void alarm_inc_hrs1();
void alarm_dec_hrs1();
#endif /* ALARMS_H_ */
