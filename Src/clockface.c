/*
 * clockface.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Parth
 */
#include "clockface.h"
#include "display.h"
#include "render.h"
#include "assets/icons/icons.h"
#include "hdc2022.h"
#include "mcp7940.h"
char time[]={'0',' ','9',' ',':',' ','0',' ','0',0};
char temp_str[4] = {' ',' ','C',0};
char hum_str[4] = {' ',' ','%',0};
char *time_erase = "             ";
#define TIME_X_CORD 15
#define TIME_Y_CORD 290
void assemble_clockface(){
		uint8_t *temp_hum;
		temp_hum = hdc2022_get_data();
		draw_string(time, COOLVETICACR200, BLACK, TIME_X_CORD, TIME_Y_CORD);
		draw_string("11 September, 2023   Sunday", HELVETICA30, BLACK, 20, 48);
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
		draw_hLine(230, 208, 169, BLACK);
		draw_vLine(230, 60, 299, BLACK);
		display_render_image((uint8_t *)image_buffer);
		create_buffer_copy();

//		display_init_partial();
//		for (int i = 0; i < 10; i++) {
//			time[8] = i + 48;
//			time[6] = i + 48;
//			time[2] = i + 48;
//			time[0] = i + 48;
//			draw_string(time_erase, COOLVETICACR200, BLACK, TIME_X_CORD, TIME_Y_CORD);
//			draw_string(time, COOLVETICACR200, BLACK, TIME_X_CORD, TIME_Y_CORD);
//			display_render_image((uint8_t*) image_buffer);
//			create_buffer_copy();
//		}
//		display_init();
//		display_render_image((uint8_t*) image_buffer);
//	create_buffer_copy();
//	display_init_partial();
}
