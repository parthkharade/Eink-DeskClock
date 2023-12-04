/*
 * font.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Parth
 */

#include "fonts.h"

uint8_t font_table_size = 0;

font_table_t font_table[] = {
		{.font_name = HELVETICA30,.font_height = 30, .font_bitmap = helvetica30_glyph_bitmap, .font_glyph_dsc = helvetica30_glyph_dsc, .glyph_offset = 32},
		{.font_name = HELVETICA90,.font_height = 90, .font_bitmap = helvetica90_glyph_bitmap, .font_glyph_dsc = helvetica90_glyph_dsc, .glyph_offset = 48},
		{.font_name = HELVETICA120,.font_height = 120, .font_bitmap = helvetica120_glyph_bitmap, .font_glyph_dsc = helvetica120_glyph_dsc, .glyph_offset = 32},
		{.font_name = COOLVETICACR180,.font_height = 180, .font_bitmap = coolveticacrammed180_glyph_bitmap, .font_glyph_dsc = coolveticacrammed180_glyph_dsc, .glyph_offset = 32},
		{.font_name = COOLVETICACR200,.font_height = 200, .font_bitmap = coolveticacrammed200_glyph_bitmap, .font_glyph_dsc = coolveticacrammed200_glyph_dsc, .glyph_offset = 32}
};

void init_fonts(){
	font_table_size = sizeof(font_table) / sizeof(font_table_t);
}
