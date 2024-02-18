/*
 * i2c.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#ifndef I2C_H_
#define I2C_H_
#include "stdint.h"

/**
 * @brief Initialises the I2C to operate at 100KHz 
 * 
 */
void i2c_init();

/**
 * @brief Sends n bytes on the I2C bus as a master
 * 
 * @param buff 
 * @param dev_add 
 * @param n_bytes 
 */
void i2c_write_bytes(uint8_t *buff,uint8_t dev_add,uint16_t n_bytes);

/**
 * @brief  Reads n_bytes from an I2C slave from the register_address 
 * 
 * @param buff 
 * @param dev_add 
 * @param register_add 
 * @param n_bytes 
 */
void i2c_read_bytes(uint8_t *buff,uint8_t dev_add,uint8_t register_add,uint16_t n_bytes);

#endif /* I2C_H_ */
