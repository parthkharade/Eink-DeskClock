/*
 * mcp7940.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Parth
 */

#include "i2c.h"
#include "mcp7940.h"
#include "systick.h"
#include "stdbool.h"
#include "timeanddate.h"

rtc_time_t mcp_curr_time;
rtc_time_t mcp_config_time;
bool change_mcp_time = false;
void init_mcp7940(){
	enable_oscillator_mcp7940();
	if(change_mcp_time){
		set_time_mcp7490();
	}
	get_time_mcp7490();

}
void enable_oscillator_mcp7940(){
	uint8_t rec_buf[1];
	i2c_read_bytes(rec_buf, MCP_DEV_ADD,0x00, 1);
	rec_buf[0] |= MCP_OSC_ST_MSK;
	uint8_t write_buf[2]= {0x00,rec_buf[0]};
	i2c_write_bytes(write_buf,0x6F, 2);
	delay_ms(200);
}
void disable_oscillator_mcp7940(){
	uint8_t rec_buf[1];
	i2c_read_bytes(rec_buf, MCP_DEV_ADD,0x00, 1);
	rec_buf[0] &= ~MCP_OSC_ST_MSK;
	uint8_t write_buf[2]= {0x00,rec_buf[0]};
	i2c_write_bytes(write_buf,0x6F, 2);
	delay_ms(200);
}
void set_time_mcp7490(){
	disable_oscillator_mcp7940();
	uint8_t set_time_buf[8] = 	{MCP_SEC,
								mcp_config_time.sec,
								mcp_config_time.min,
								mcp_config_time.hrs,
								mcp_config_time.day,
								mcp_config_time.date,
								mcp_config_time.month,
								mcp_config_time.year};
	i2c_write_bytes(set_time_buf, MCP_DEV_ADD, 8);
	delay_ms(10);
	enable_oscillator_mcp7940();
}
void  get_time_mcp7490(){
	uint8_t time_buf[7];
	i2c_read_bytes(time_buf, MCP_DEV_ADD,0x00, 7);
	mcp_curr_time.sec 	=	time_buf[0];
	mcp_curr_time.min 	=	time_buf[1];
	mcp_curr_time.hrs 	=	time_buf[2];
	mcp_curr_time.day  =	time_buf[3];
	mcp_curr_time.date =	time_buf[4];
	mcp_curr_time.month =	time_buf[5];
	mcp_curr_time.year	=	time_buf[6];
}
