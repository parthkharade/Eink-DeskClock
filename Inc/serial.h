/*
 * serial.h
 *
 *  Created on: Oct 24, 2023
 *      Author: Parth
 */

#ifndef SERIAL_H_
#define SERIAL_H_
#include "stdint.h"

void init_serial();
char get_char();
void put_char(char c);
void put_str(char *c);
void put_num(uint8_t num);
#endif /* SERIAL_H_ */
