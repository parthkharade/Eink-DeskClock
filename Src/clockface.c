/*
 * clockface.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Parth
 */
#include "clockface.h"
#include "display.h"
#include "render.h"
#include "assets/fonts/fonts.h"
#include "hdc2022.h"
#include "mcp7940.h"
#include "string.h"

rtc_time_t mcp_curr_time;


char temp_str[4] = {' ',' ','C',0};
char hum_str[4] = {' ',' ','%',0};
char date_str[31];
char time_str[9];
const char *time_erase = "             ";
const char *days_of_week[] = { "Monday", "Tuesday", "Wednesday", "Thursday",
		"Friday", "Saturday", "Sunday" };
const char *months_of_year[] =
		{ "January", "February", "March", "April", "May", "June", "July",
				"August", "September", "October", "November", "December" };
const char *dates_of_month[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21",
		"22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };
const char *years_of_decade[] = { "2020", "2021", "2022", "2023", "2024",
		"2025", "2026", "2027", "2028", "2029" };


const char *hours_of_day[] =  {
        "0 0 ", "0 1 ", "0 2 ", "0 3 ", "0 4 ", "0 5 ", "0 6 ", "0 7 ",
        "0 8 ", "0 9 ", "1 0 ", "1 1 ", "1 2 ", "1 3 ", "1 4 ", "1 5 ",
        "1 6 ", "1 7 ", "1 8 ", "1 9 ", "2 0 ", "2 1 ", "2 2 ", "2 3 "
    };

const char *minutes_of_hour[] = {
    " 0 0", " 0 1", " 0 2", " 0 3", " 0 4", " 0 5", " 0 6", " 0 7", " 0 8", " 0 9",
    " 1 0", " 1 1", " 1 2", " 1 3", " 1 4", " 1 5", " 1 6", " 1 7", " 1 8", " 1 9",
    " 2 0", " 2 1", " 2 2", " 2 3", " 2 4", " 2 5", " 2 6", " 2 7", " 2 8", " 2 9",
    " 3 0", " 3 1", " 3 2", " 3 3", " 3 4", " 3 5", " 3 6", " 3 7", " 3 8", " 3 9",
    " 4 0", " 4 1", " 4 2", " 4 3", " 4 4", " 4 5", " 4 6", " 4 7", " 4 8", " 4 9",
    " 5 0", " 5 1", " 5 2", " 5 3", " 5 4", " 5 5", " 5 6", " 5 7", " 5 8", " 5 9"
};
#define TIME_X_CORD 15
#define TIME_Y_CORD 290

#define DATE_X_CORD 20
#define DATE_Y_CORD 48

void assemble_clockface(){
		uint8_t *temp_hum;
		temp_hum = hdc2022_get_data();
		mcp_curr_time = get_time_mcp7490();
		clockface_assemble_time();
		clockface_assemble_date(HELVETICA30);
//		draw_image(weather_icons, 220, 64, 64, 64);
//		draw_string("Boulder",HELVETICA30,BLACK,284,30);
//		draw_string("H:-4/L:-13",HELVETICA30,BLACK,284,60);
		draw_string("ALARMS",HELVETICA30, BLACK, 265, 90);
		draw_string("17:00", HELVETICA30, BLACK, 238, 118);
		draw_string("08:00", HELVETICA30, BLACK, 238, 146);
		draw_string("09:00", HELVETICA30, BLACK, 238, 174);
		draw_string("10:00", HELVETICA30, BLACK, 238, 202);
		draw_string("ROOM", HELVETICA30, BLACK, 280, 236);
		temp_str[0] = temp_hum[0]/10+48;
		temp_str[1] = temp_hum[0]%10+48;

		hum_str[0] = temp_hum[1]/10+48;
		hum_str[1] = temp_hum[1]%10+48;
		draw_string("TEMP ", HELVETICA30, BLACK, 238, 264);
		draw_string("RH   ", HELVETICA30, BLACK, 240, 292);
		draw_string(":", HELVETICA30, BLACK, 330, 264);
		draw_string(":   ", HELVETICA30, BLACK, 330, 292);
		draw_string(temp_str, HELVETICA30, BLACK, 342, 264);
		draw_string(hum_str, HELVETICA30, BLACK, 342, 292);

		draw_hLine(0, 60, 399, BLACK);
		draw_hLine(232, 208, 169, BLACK);
		draw_vLine(232, 60, 299, BLACK);
		display_render_image((uint8_t *)image_buffer);
		create_buffer_copy();

}

void clockface_assemble_date(font_t font){
	uint8_t temp_var; // temp var to hold bcd to decimal conversion of values.

	temp_var = ((mcp_curr_time.date>>4)&0x0F)*10 +(mcp_curr_time.date&0x0F);
	strcat(date_str,dates_of_month[temp_var-1]);
	strcat(date_str," ");
	temp_var = ((mcp_curr_time.month>>4)&0x0F)*10 +(mcp_curr_time.month&0x0F);
	strcat(date_str,months_of_year[temp_var-1]);
	strcat(date_str,", ");
	temp_var = ((mcp_curr_time.year>>4)&0x0F)*10 +(mcp_curr_time.year&0x0F);
	strcat(date_str,years_of_decade[temp_var-20]);
	strcat(date_str,"   ");
	temp_var = (mcp_curr_time.day&0x0F);
	strcat(date_str,days_of_week[temp_var-1]);

	char *temp_str = date_str;
	uint16_t date_str_width = 0;
	while(*temp_str){
		date_str_width+=font_table[font].font_glyph_dsc[*temp_str-font_table[font].glyph_offset].w_px;
		temp_str++;
	}

	uint16_t date_x_cord = (uint16_t)((DISPLAY_WIDTH-date_str_width)/2);
	draw_string(date_str, font, BLACK, date_x_cord , DATE_Y_CORD);
}

void clockface_assemble_time(){
	uint8_t temp_var; // temp var to hold bcd to decimal conversion of values.
	temp_var = ((mcp_curr_time.hrs>>4)&0x01)*10 +(mcp_curr_time.hrs&0x0F);
	strcat(time_str,hours_of_day[temp_var-1]);
	strcat(time_str,":");
	temp_var = ((mcp_curr_time.min>>4)&0x07)*10 +(mcp_curr_time.min&0x0F);
	strcat(time_str,minutes_of_hour[temp_var-1]);
	draw_string(time_str, COOLVETICACR200, BLACK, TIME_X_CORD , TIME_Y_CORD);
}

void clockface_assemble_alarms(){

}

void clockface_assemble_temp(){

}

void clockface_update_time(){

}
void clockface_update_date(){

}
void clockface_update_temp(){

}
void clockface_update_alarms(){

}
