/*
 * clockface.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Parth
 */

#ifndef CLOCKFACE_H_
#define CLOCKFACE_H_

#include "assets/fonts/fonts.h"

extern uint8_t update_clockface;
void assemble_clockface();
void clockface_assemble_date(font_t font);
void clockface_assemble_time();
void clockface_assemble_alarms();
void clockface_update();
#endif /* CLOCKFACE_H_ */
