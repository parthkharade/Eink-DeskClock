/*
 * i2c.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#ifndef I2C_H_
#define I2C_H_
#include "stdint.h"
void i2c_init();
void i2c_write_bytes(uint8_t *buff,uint8_t dev_add,uint16_t n_bytes);
void i2c_read_bytes(uint8_t *buff,uint8_t dev_add,uint8_t register_add,uint16_t n_bytes);

#endif /* I2C_H_ */
