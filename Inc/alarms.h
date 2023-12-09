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
	uint8_t alarm_enb;
}alarm_t;
extern uint8_t alarm_index;
extern alarm_t alarm_table[];
alarm_t *get_alarms();
void alarm_toggle();
void alarm_inc_index();

void alarm_inc_min0();
void alarm_dec_min0();
void alarm_inc_min1();
void alarm_dec_min1();

void alarm_inc_hrs0();
void alarm_dec_hrs0();
void alarm_inc_hrs1();
void alarm_dec_hrs1();
#endif /* ALARMS_H_ */
