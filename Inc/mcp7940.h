/*
 * mcp7940.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Parth
 */

#ifndef MCP7940_H_
#define MCP7940_H_

typedef struct{
	uint8_t sec;
	uint8_t min;
	uint8_t hrs;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_time_t;

#define MCP_DEV_ADD 0x6F
#define MCP_SEC		0x00
#define MCP_MIN     0x01
#define MCP_HRS     0x02
#define MCP_DAY     0x03
#define MCP_DATE    0x04
#define MCP_MTH     0x05
#define MCP_YEAR    0x06
#define MCP_CTRL    0x07

#define MCP_OSC_ST_MSK 	(1<<7)
#define MCP_12HR_MSK 	(1<<6)
#define MCP_OSC_STS_MSK (1<<5)
#define MCP_EXT_OSC_MSK (1<<3)
void init_mcp7940();
void enable_oscillator_mcp7940();
void disable_oscillator_mcp7940();
void set_time_mcp7490();
rtc_time_t get_time_mcp7490();
#endif /* MCP7940_H_ */
