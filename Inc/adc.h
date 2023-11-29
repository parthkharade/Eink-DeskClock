/*
 * adc.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Parth
 */

#ifndef ADC_H_
#define ADC_H_
#include "stm32f411xe.h"
/**
 * @brief Initiliases ADC1 to sample Channel 1 PA1 using a software trigger.
 * 
 */
void init_adc();
/**
 * @brief Gets the reading of the PA1 which is connected to the DAC Voltage.
 * 
 * @return uint8_t 
 */
uint8_t adc_get_dac_volt();

#endif /* ADC_H_ */
