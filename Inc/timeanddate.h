/*
 * timeanddate.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Parth
 */

#ifndef TIMEANDDATE_H_
#define TIMEANDDATE_H_
#include "mcp7940.h"

/**
 * @brief Reads the latest time from the MCP7490 
 * 
 */
void update_time();

/**
 * @brief Checks if time (minutes) has changed since the last read.  
 * 
 * @return uint8_t 
 */
uint8_t check_time_diff();

// Refer to alarms.h . Self explanatory.
void time_inc_min0();
void time_inc_min1();
void time_inc_hrs0();
void time_inc_hrs1();
#endif /* TIMEANDDATE_H_ */
