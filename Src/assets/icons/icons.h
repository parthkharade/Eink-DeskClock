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

//typedef enum{
//	CLEAR_DAY,
//	CLEAR_NIGHT,
//};

extern const uint8_t weather_icons[];

#endif /* ASSETS_ICONS_ICONS_H_ */
