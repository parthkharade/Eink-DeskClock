/*
 * render.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Parth
 */

#ifndef RENDER_H_
#define RENDER_H_
#include "stdint.h"
#include "assets/fonts/fonts.h"

extern uint8_t image_buffer[15000];
typedef enum{
	BLACK,
	WHITE
}colour_t;




void draw_string(char *str, font_t font, colour_t font_colour, uint16_t x, uint16_t y);
void draw_char(const uint8_t *glyph_add, uint8_t glyph_width, uint8_t glyph_height, uint16_t x, uint16_t y,colour_t colour);
void draw_hLine(uint16_t x, uint16_t y, uint16_t len,colour_t colour);
void draw_vLine(uint16_t x, uint16_t y, uint16_t len,colour_t colour);
void draw_image(const uint8_t *image_data, uint16_t x,uint16_t y, uint16_t width, uint16_t height);
void draw_pixel(uint16_t x,uint16_t y,colour_t colour);
void clear_area(uint16_t x,uint16_t y);
void set_area(uint16_t x, uint16_t y);
void init_draw_module();
#endif /* RENDER_H_ */

