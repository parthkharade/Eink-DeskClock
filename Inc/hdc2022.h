/*
 * hdc2022.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#ifndef HDC2022_H_
#define HDC2022_H_

#include "stdint.h"
void send_some_data();
uint16_t read_device_id();
void hdc2022_trigger_measurement();
uint8_t *hdc2022_get_data();
#endif /* HDC2022_H_ */
