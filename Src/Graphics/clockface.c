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
#include "statemachine.h"
#include "alarms.h"
#include "assets/icons/icons.h"
#include "timeanddate.h"
uint8_t partial_update_count = 0;
uint8_t update_clockface = 0;

/* Strings to store field values*/
char temp_str[4] = {' ',' ','C',0};
char hum_str[4] = {' ',' ','%',0};
char date_str[31];
char time_str[9];

/*String to earse the time field*/

/**
 * @brief Static const strings to store days months hours and minutes 
 * 
 */
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


const char *hours_of_day_wspaces[] =  {
        "0 0 ", "0 1 ", "0 2 ", "0 3 ", "0 4 ", "0 5 ", "0 6 ", "0 7 ",
        "0 8 ", "0 9 ", "1 0 ", "1 1 ", "1 2 ", "1 3 ", "1 4 ", "1 5 ",
        "1 6 ", "1 7 ", "1 8 ", "1 9 ", "2 0 ", "2 1 ", "2 2 ", "2 3 "
    };

const char *minutes_of_hour_wspaces[] = {
    " 0 0", " 0 1", " 0 2", " 0 3", " 0 4", " 0 5", " 0 6", " 0 7", " 0 8", " 0 9",
    " 1 0", " 1 1", " 1 2", " 1 3", " 1 4", " 1 5", " 1 6", " 1 7", " 1 8", " 1 9",
    " 2 0", " 2 1", " 2 2", " 2 3", " 2 4", " 2 5", " 2 6", " 2 7", " 2 8", " 2 9",
    " 3 0", " 3 1", " 3 2", " 3 3", " 3 4", " 3 5", " 3 6", " 3 7", " 3 8", " 3 9",
    " 4 0", " 4 1", " 4 2", " 4 3", " 4 4", " 4 5", " 4 6", " 4 7", " 4 8", " 4 9",
    " 5 0", " 5 1", " 5 2", " 5 3", " 5 4", " 5 5", " 5 6", " 5 7", " 5 8", " 5 9"
};
const char *hours_of_day[] =  {
        "00", "01", "02", "03", "04", "05", "06", "07",
        "08", "09", "10", "11", "12", "13", "14", "15",
        "16", "17", "18", "19", "20", "21", "22", "23"
    };

const char *minutes_of_hour[] = {
    "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
    "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
    "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
    "50", "51", "52", "53", "54", "55", "56", "57", "58", "59"
};

// XY coordinates for time and date.
#define TIME_X_CORD 15
#define TIME_Y_CORD 290

#define DATE_X_CORD 20
#define DATE_Y_CORD 48

void assemble_clockface(){

		get_time_mcp7490();
		clockface_assemble_time();
		clockface_assemble_date(COOLVETICA30);
		clockface_assemble_alarms();
		clockface_assemble_temp();

		// Lines to bifuracte different areas on the display
		draw_hLine(0, 60, 399, BLACK);
		draw_hLine(232, 208, 169, BLACK);
		draw_vLine(232, 60, 299, BLACK);
}

void clockface_update(){
	if(update_clockface){
		assemble_clockface();
		if(partial_update_count>=9){
			display_init();
			display_render_image((uint8_t *)image_buffer);
			display_init_partial();
			partial_update_count = 0;
		}
		else{
			display_render_image((uint8_t *)image_buffer);
			partial_update_count++;
		}
		update_clockface = 0;
	}
}
void clockface_assemble_date(font_t font){
	uint8_t temp_var; // temp var to hold bcd to decimal conversion of values.

	*date_str = 0;
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

	// Calculate the x cord so that the date is centered on the display
	uint16_t date_x_cord = (uint16_t)((DISPLAY_WIDTH-date_str_width)/2);
	draw_string(date_str, font, BLACK, date_x_cord , DATE_Y_CORD);

}

void clockface_assemble_time(){
	*time_str = 0;
	uint8_t temp_var; // temp var to hold bcd to decimal conversion of values.

	if(curr_state >= TIME_CONFIG_UPD_MIN0 && curr_state <= TIME_CONFIG_UPD_HRS1){
		temp_var = ((mcp_config_time.hrs>>4)&0x03)*10 +(mcp_config_time.hrs&0x0F);
		strcat(time_str,hours_of_day_wspaces[temp_var]);
		strcat(time_str,":");
		temp_var = ((mcp_config_time.min>>4)&0x07)*10 +(mcp_config_time.min&0x0F);
		strcat(time_str,minutes_of_hour_wspaces[temp_var]);
		draw_string(time_str, COOLVETICACR200, BLACK, TIME_X_CORD , TIME_Y_CORD);


		/**
		 * @brief If the user is in time configuration mode this part draws a line under the selected digit.
		 * 
		 */
		if(curr_state == TIME_CONFIG_UPD_MIN0){
			draw_hLine(TIME_X_CORD + (32*0 + 16*0 +12*0) , (TIME_Y_CORD - 40), (32*3 + 16*4 +12*1)	, WHITE);
			draw_hLine(TIME_X_CORD + (32*3 + 16*4 +12*1) , (TIME_Y_CORD - 40), (32*1 + 16*0 +12*0)	, BLACK);

		}
		else if(curr_state == TIME_CONFIG_UPD_MIN1){
			draw_hLine(TIME_X_CORD + (32*0 + 16*0 +12*0), (TIME_Y_CORD - 40), (32*2 + 16*3 + 12*1)	, WHITE);
			draw_hLine(TIME_X_CORD + (32*2 + 16*3 +12*1), (TIME_Y_CORD - 40), (32*1 + 16*0 + 12*0)	, BLACK);
			draw_hLine(TIME_X_CORD + (32*3 + 16*3 +12*1), (TIME_Y_CORD - 40), (32*1 + 16*1 + 12*0)	, WHITE);
		}
		else if(curr_state == TIME_CONFIG_UPD_HRS0){
			draw_hLine(TIME_X_CORD + (32*0 + 16*0 +12*0), (TIME_Y_CORD - 40), (32*1 + 16*1 + 12*0) 	, WHITE);
			draw_hLine(TIME_X_CORD + (32*1 + 16*1 +12*0), (TIME_Y_CORD - 40), (32*1 + 16*0 + 12*0)	, BLACK);
			draw_hLine(TIME_X_CORD + (32*2 + 16*1 +12*0), (TIME_Y_CORD - 40), (32*2 + 16*3 + 12*1)	, WHITE);
		}
		else
		{
			draw_hLine(TIME_X_CORD + (32*0 + 16*0 +12*0), (TIME_Y_CORD - 40), (32*1 + 16*0 +12*0)	, BLACK);
			draw_hLine(TIME_X_CORD + (32*1 + 16*0 +12*0), (TIME_Y_CORD - 40), (32*3 + 16*4 +12*1)	, WHITE);
		}
	}
	else
	{
		temp_var = ((mcp_curr_time.hrs>>4)&0x03)*10 +(mcp_curr_time.hrs&0x0F);
		strcat(time_str,hours_of_day_wspaces[temp_var]);
		strcat(time_str,":");
		temp_var = ((mcp_curr_time.min>>4)&0x07)*10 +(mcp_curr_time.min&0x0F);
		strcat(time_str,minutes_of_hour_wspaces[temp_var]);
		draw_string(time_str, COOLVETICACR200, BLACK, TIME_X_CORD , TIME_Y_CORD);
	}
}

void clockface_assemble_alarms(){
	draw_string("ALARMS",COOLVETICA30, BLACK, 265, 90);
	uint8_t temp_var; 	// temp var to hold bcd to decimal conversion of values.
	alarm_t *alarm_table = get_alarms();
	for(int i = 0;i<4;i++){
		*time_str = 0;
		temp_var = ((alarm_table[i].alarm_hrs>>4)&0x03)*10 +(alarm_table[i].alarm_hrs&0x0F);
		strcat(time_str,hours_of_day[temp_var]);
		strcat(time_str,":");
		temp_var = ((alarm_table[i].alarm_min>>4)&0x07)*10 +(alarm_table[i].alarm_min&0x0F);
		strcat(time_str,minutes_of_hour[temp_var]);
		draw_string(time_str, COOLVETICA30, BLACK, 238, 118 + i*28);

		// Draw and arrow pointing to the selected alarm and a underline showwing the selected digit.
		if(curr_state >= ALARM_CONFIG_SELECT && curr_state <= ALARM_CONFIG_UPD_HRS1){
			uint16_t arrow_x_cord = 238 + 70;
			uint16_t arrow_y_cord = 118 + i*28;
			if(alarm_index == i){
				draw_string("<--", COOLVETICA30, BLACK, arrow_x_cord, arrow_y_cord);
			}
			else{
				draw_string("    ", COOLVETICA30, BLACK, arrow_x_cord, arrow_y_cord);
			}

			// Similar to the line drawing for time config but is a bit messier.
			if(curr_state == ALARM_CONFIG_UPD_MIN0){
				uint16_t highlight_y_cord = 118 + alarm_index*28-3;
				draw_hLine(238, highlight_y_cord, 48, WHITE);
				draw_hLine(238+48, highlight_y_cord, 14, BLACK);

			}
			else if(curr_state == ALARM_CONFIG_UPD_MIN1){
				uint16_t highlight_y_cord = 118 + alarm_index*28-3;
				draw_hLine(238, highlight_y_cord, 34, WHITE);
				draw_hLine(238+34, highlight_y_cord, 14, BLACK);
				draw_hLine(238+48, highlight_y_cord,14, WHITE);

			}
			else if(curr_state == ALARM_CONFIG_UPD_HRS0){
				uint16_t highlight_y_cord = 118 + alarm_index*28-3;
				draw_hLine(238, highlight_y_cord, 14, WHITE);
				draw_hLine(238+14, highlight_y_cord, 14, BLACK);
				draw_hLine(238+28, highlight_y_cord, 34, WHITE);

			}
			else if(curr_state == ALARM_CONFIG_UPD_HRS1){
				uint16_t highlight_y_cord = 118 + alarm_index*28-3;
				draw_hLine(238, highlight_y_cord, 14, BLACK);
				draw_hLine(238+14, highlight_y_cord, 48, WHITE);
			}
		}
		else
		{
			uint16_t arrow_x_cord = 238 + 70;
			uint16_t arrow_y_cord = 118 + i*28;
			draw_string("    ", COOLVETICA30, BLACK, arrow_x_cord, arrow_y_cord);
		}

		if(alarm_table[i].usr_alarm_enb){
			uint16_t icon_x_cord = 350;
			uint16_t icon_y_cord = 118 + i*28;
			const uint8_t *icon_data = misc_icons + misc_icon_dsc_table[ALARM_ICON].icon_index;
			draw_image(icon_data, icon_x_cord, icon_y_cord, 32, 32);
		}
		else{
			uint16_t icon_x_cord = 350;
			uint16_t icon_y_cord = 118 + i*28;
			const uint8_t *icon_data = misc_icons + misc_icon_dsc_table[BLANK_32x32].icon_index;
			draw_image(icon_data, icon_x_cord, icon_y_cord, 32, 32);
		}
	}

}

void clockface_assemble_temp(){
	uint8_t *temp_hum;
	temp_hum = hdc2022_get_data();
	draw_string("ROOM", COOLVETICA30, BLACK, 280, 236);
	temp_str[0] = temp_hum[0]/10+48;
	temp_str[1] = temp_hum[0]%10+48;

	hum_str[0] = temp_hum[1]/10+48;
	hum_str[1] = temp_hum[1]%10+48;
	draw_string("TEMP ", COOLVETICA30, BLACK, 238, 264);
	draw_string("RH   ", COOLVETICA30, BLACK, 240, 292);
	draw_string(":", COOLVETICA30, BLACK, 330, 264);
	draw_string(":   ", COOLVETICA30, BLACK, 330, 292);
	draw_string(temp_str, COOLVETICA30, BLACK, 342, 264);
	draw_string(hum_str, COOLVETICA30, BLACK, 342, 292);
}


