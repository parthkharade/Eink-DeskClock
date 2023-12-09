/*
 * icons.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#ifndef ASSETS_ICONS_ICONS_H_
#define ASSETS_ICONS_ICONS_H_


#include "stdint.h"

typedef struct{
	uint8_t width;
	uint16_t icon_index;
}icon_dsc_t;

typedef enum{
	BLANK_32x32,
	ALARM_ICON
}misc_icons_t;

extern const uint8_t misc_icons[];
extern const icon_dsc_t misc_icon_dsc_table[];
#endif /* ASSETS_ICONS_ICONS_H_ */
