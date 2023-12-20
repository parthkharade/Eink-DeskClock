/*
 * font.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Parth
 */

#include "assets/fonts/fonts.h"

uint8_t font_table_size = 0;

font_table_t font_table[] = {
		{.font_name = COOLVETICA30,.font_height = 30, .font_bitmap = coolvetica30_glyph_bitmap, .font_glyph_dsc = coolvetica30_glyph_dsc, .glyph_offset = 32},
		{.font_name = COOLVETICACR200,.font_height = 200, .font_bitmap = coolveticacrammed200_glyph_bitmap, .font_glyph_dsc = coolveticacrammed200_glyph_dsc, .glyph_offset = 32}
};

void init_fonts(){
	font_table_size = sizeof(font_table) / sizeof(font_table_t);
}
