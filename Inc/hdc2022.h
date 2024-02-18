/*
 * hdc2022.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#ifndef HDC2022_H_
#define HDC2022_H_

#include "stdint.h"

/**
 * @brief triggers a measurement on the HDC2022 temperature sensor
 * 
 */
void hdc2022_trigger_measurement();

/**
 * @brief Reads data from the HDC2022 temperature sensor 
 * 
 * @return uint8_t* 
 */
uint8_t *hdc2022_get_data();
#endif /* HDC2022_H_ */
