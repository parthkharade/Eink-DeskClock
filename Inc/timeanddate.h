/*
 * timeanddate.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */

#ifndef TIMEANDDATE_H_
#define TIMEANDDATE_H_
#include "mcp7940.h"
void update_time();
uint8_t check_time_diff();

void time_inc_min0();
void time_inc_min1();
void time_inc_hrs0();
void time_inc_hrs1();
#endif /* TIMEANDDATE_H_ */
