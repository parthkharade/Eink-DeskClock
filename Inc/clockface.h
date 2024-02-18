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

/**
 * @brief Assembles the clockface in the image buffer by calling various helper functions.
 * 
 */
void assemble_clockface();

/**
 * @brief Assembles the date feild of the clockface. 
 * 
 * @param font 
 */
void clockface_assemble_date(font_t font);

/**
 * @brief Assembles the time feild of the clockface 
 * 
 */
void clockface_assemble_time();

/**
 * @brief Assembles the alarms field of the clockface.
 * 
 */
void clockface_assemble_alarms();

/**
 * @brief Calls the display refresh functions to update the clockface
 * 
 */
void clockface_update();

/**
 * @brief Assembles the temperature and humidity field of the clockface.
 * 
 */
void clockface_assemble_temp();
#endif /* CLOCKFACE_H_ */
