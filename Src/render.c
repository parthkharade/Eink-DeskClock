/*
 * render.c
 *
 *  Created on: Dec 2, 2023
 *      Author: Parth
 */



#include "render.h"
#include "stdbool.h"
#include "display.h"
#include "string.h"
uint8_t image_buffer[DISPLAY_BUFFER_SIZE];
uint8_t old_image_buffer[DISPLAY_BUFFER_SIZE];
void draw_string(char* str, font_t font, colour_t font_colour, uint16_t x, uint16_t y) {
	int i = 0;
	for (i = 0;i < font_table_size;i++) {
		if (font == font_table[i].font_name)
			break;
	}
	const uint8_t* font_bitmap = font_table[i].font_bitmap;
	uint8_t font_height = font_table[i].font_height;
	const font_glyph_dsc_t* font_glyph_dsc = font_table[i].font_glyph_dsc;
	const uint8_t glyph_offset = font_table[i].glyph_offset;
	uint16_t x_temp = x;
	uint16_t y_temp = y;
	while(*str){
		const uint8_t *glyph_add = (font_bitmap + font_glyph_dsc[*str-glyph_offset].glyph_index);
		uint8_t glyph_width = font_glyph_dsc[*str-glyph_offset].w_px;
		draw_char(glyph_add, glyph_width, font_height, x, y,font_colour);
		x+=glyph_width;
		str++;
	}
}


void draw_char(const uint8_t *glyph_add, uint8_t glyph_width, uint8_t glyph_height, uint16_t x, uint16_t y,colour_t colour) {

	uint16_t y_glyph_top = y - glyph_height + 1; // get the top row of the glyph to be rendered.
	uint16_t x_temp = x; // Store the x coordinate in a temp variable
	uint16_t glyph_width_bytes = ((glyph_width % 8) == 0) ? (glyph_width / 8) : (glyph_width / 8 + 1); // Calculate how wide the glyph is in bytes
	uint16_t image_buf_index = 0; // Variable to store image buffer index
	for (uint16_t i = 0;i < glyph_height;i++) { // iterate along the length of the glyph one row at a time.
		x_temp = x; // At the start of each iteration reinitialise the x coordinate to the starting column
		for (uint16_t j = 0; j < glyph_width_bytes; j++) { // Iterate along the row of the glyph one byte at a time.
			image_buf_index = ((y_glyph_top + i) * 50) + x_temp/8;
			if (x_temp/8 == DISPLAY_WIDTH/8 - 1) {

			} else {
				uint8_t curr_byte_bits = 8 - x_temp%8; // How many bits from the current byte of the glyph can be stored in the current byte of the image buffer.
				uint8_t next_byte_bits = 8 - curr_byte_bits;// How many bits from the current byte of the glyph are to be stored in the next byte of the image buffer.
				uint8_t curr_byte_mask = (1<<curr_byte_bits)-1;
				uint8_t next_byte_mask = ((1<<next_byte_bits)-1)<<(8-next_byte_bits);
				if(colour == BLACK){
					image_buffer[image_buf_index]	 &= ~((0xFF>>(8-curr_byte_bits)&curr_byte_mask)); // Clear the pixels first
					image_buffer[image_buf_index]	 |= (glyph_add[i*glyph_width_bytes + j]>>(8-curr_byte_bits)&curr_byte_mask); // Set bits in current byte of image buffer.
					image_buffer[image_buf_index + 1]&= ~((0xFF<<(8-next_byte_bits)&next_byte_mask)); // Clear the pixels first
					image_buffer[image_buf_index + 1]|= (glyph_add[i*glyph_width_bytes + j]<<(8-next_byte_bits)&next_byte_mask);// Set bits in next byte of image buffer.
				}
				else{
					image_buffer[image_buf_index]	 |= ((0xFF>>(8-curr_byte_bits)&curr_byte_mask));
					image_buffer[image_buf_index]	 &= ~((glyph_add[i*glyph_width_bytes + j]>>(8-curr_byte_bits)&curr_byte_mask));
					image_buffer[image_buf_index + 1]|= ((0xFF<<(8-next_byte_bits)&next_byte_mask));
					image_buffer[image_buf_index + 1]&= ~((glyph_add[i*glyph_width_bytes + j]<<(8-next_byte_bits)&next_byte_mask));
				}
				x_temp += 8;
			}
		}
	}
}

void draw_image(const uint8_t *image_data, uint16_t x,uint16_t y, uint16_t width, uint16_t height){
	uint16_t y_glyph_top = y - height + 1;
	uint16_t x_temp = x;
	uint16_t width_bytes = ((width % 8) == 0) ? (width / 8) : (width / 8 + 1);
	uint16_t image_buf_index = 0;
	for(int i = 0;i<height;i++){
		x_temp = x;
		for(int j=0;j<width_bytes;j++){
			image_buf_index = ((y_glyph_top + i) * 50) + x_temp/8;
			uint8_t curr_byte_bits = 8 - x_temp%8; // How many bits from the current byte of the glyph can be stored in the current byte of the image buffer.
			uint8_t next_byte_bits = 8 - curr_byte_bits;// How many bits from the current byte of the glyph are to be stored in the next byte of the image buffer.
			uint8_t curr_byte_mask = (1<<curr_byte_bits)-1;
			uint8_t next_byte_mask = ((1<<next_byte_bits)-1)<<(8-next_byte_bits);
			image_buffer[image_buf_index]	 &= ~((0xFF>>(8-curr_byte_bits)&curr_byte_mask)); // Clear the pixels first
			image_buffer[image_buf_index]	 |= (image_data[i*width_bytes + j]>>(8-curr_byte_bits)&curr_byte_mask); // Set bits in current byte of image buffer.
			image_buffer[image_buf_index + 1]&= ~((0xFF<<(8-next_byte_bits)&next_byte_mask)); // Clear the pixels first
			image_buffer[image_buf_index + 1]|= (image_data[i*width_bytes + j]<<(8-next_byte_bits)&next_byte_mask);// Set bits in next byte of image buffer.
			x_temp += 8;
		}
	}
}
void draw_hLine(uint16_t x,uint16_t y, uint16_t len,colour_t colour){

	for(uint16_t i = x;i<x+len;i++){
		draw_pixel(i, y, colour);
	}
}
void draw_vLine(uint16_t x,uint16_t y, uint16_t len,colour_t colour){
	for(uint16_t i = y;i<y+len;i++){
		draw_pixel(x, i, colour);
	}
}
void draw_pixel(uint16_t x,uint16_t y,colour_t colour){
	uint8_t mask = (1 << (7 - x%8));
	uint16_t image_buf_index = y*50 + x/8;
	if(colour == BLACK){
		image_buffer[image_buf_index] |= mask;
	}
	else{
		image_buffer[image_buf_index] &= ~mask;
	}
}
void create_buffer_copy(){
	memcpy(old_image_buffer,image_buffer,DISPLAY_BUFFER_SIZE);
}

