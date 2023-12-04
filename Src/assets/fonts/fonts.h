/*
 * fonts.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Parth
 */

#ifndef FONTS_FONTS_H_
#define FONTS_FONTS_H_
#include "stdint.h"
typedef struct {
	uint8_t w_px;
	uint16_t glyph_index;
}font_glyph_dsc_t;

typedef enum{
	HELVETICA30,
	HELVETICA90,
	HELVETICA120,
	COOLVETICACR180,
	COOLVETICACR200
}font_t;

typedef struct {
	font_t font_name;
	uint8_t font_height;
	const uint8_t *font_bitmap;
	const font_glyph_dsc_t *font_glyph_dsc;
	const uint8_t glyph_offset;
}font_table_t;


void init_fonts();
extern font_table_t font_table[];
extern uint8_t font_table_size;
extern const uint8_t helvetica30_glyph_bitmap[];
extern const font_glyph_dsc_t helvetica30_glyph_dsc[];


extern const uint8_t helvetica90_glyph_bitmap[];
extern const font_glyph_dsc_t helvetica90_glyph_dsc[];

extern const uint8_t helvetica120_glyph_bitmap[];
extern const font_glyph_dsc_t helvetica120_glyph_dsc[];

extern const uint8_t coolveticacrammed180_glyph_bitmap[];
extern const font_glyph_dsc_t coolveticacrammed180_glyph_dsc[];

extern const uint8_t coolveticacrammed200_glyph_bitmap[];
extern const font_glyph_dsc_t coolveticacrammed200_glyph_dsc[];
#endif /* FONTS_FONTS_H_ */
