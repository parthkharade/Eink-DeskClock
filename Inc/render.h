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
extern uint8_t old_image_buffer[15000];
typedef enum{
	BLACK,
	WHITE
}colour_t;


/**
 * @brief 
 * 
 * 
 * DISPLAY CO-ORDINATE SYSTEM
 * 
 * (0,0)(top left)                                                          (299,0)(top right)
 * _____________________________________________________________________________
 * |
 * |
 * |
 * |
 * |
 * |
 * |
 * |
 * (0,399)
 */


/**
 * @brief Render str at (x,y) in font and colour font_colour. Uses iterative calls to draw_char()
 * 
 * @param str 
 * @param font 
 * @param font_colour 
 * @param x 
 * @param y 
 */
void draw_string(char *str, font_t font, colour_t font_colour, uint16_t x, uint16_t y);

/**
 * @brief Renders the character at the pointer address glyph_add at (x,y). Width and Height are used to determine the length of the 
 * 			glyph in bytes.
 * 
 * @param glyph_add 
 * @param glyph_width 
 * @param glyph_height 
 * @param x 
 * @param y 
 * @param colour 
 */
void draw_char(const uint8_t *glyph_add, uint8_t glyph_width, uint8_t glyph_height, uint16_t x, uint16_t y,colour_t colour);

/**
 * @brief Draws a horizontal line of length len starting at x,y and extedning towards the right.
 * 
 * @param x 
 * @param y 
 * @param len 
 * @param colour 
 */
void draw_hLine(uint16_t x, uint16_t y, uint16_t len,colour_t colour);

/**
 * @brief Draws a vertical line of length len start at x,y and extedning downwards in the display 
 * 
 * @param x 
 * @param y 
 * @param len 
 * @param colour 
 */
void draw_vLine(uint16_t x, uint16_t y, uint16_t len,colour_t colour);

/**
 * @brief Draws an image at a x,y in the image buffer. 
 * 
 * @param image_data 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 */
void draw_image(const uint8_t *image_data, uint16_t x,uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Draws a pixel at x,y in the specified colour 
 * 
 * @param x 
 * @param y 
 * @param colour 
 */
void draw_pixel(uint16_t x,uint16_t y,colour_t colour);

/**
 * @brief Clears a particular area to white in the buffer 
 * 
 * @param x 
 * @param y 
 */
void clear_area(uint16_t x,uint16_t y);

/**
 * @brief Sets a particular area to black in the buffer.
 * 
 * @param x 
 * @param y 
 */
void set_area(uint16_t x, uint16_t y);
/**
 * @brief Creates a copy of the image buffer.
 * 
 */
void create_buffer_copy();
#endif /* RENDER_H_ */

