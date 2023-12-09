/*
 * gpio.h
 *
 *  Created on: Oct 6, 2023
 *      Author: Parth
 */

#ifndef GPIO_H_
#define GPIO_H_

#define NVIC_GPIO_OFFSET	6U

/**
 * @brief 		: 	Initialise GPIO for Chip Select Signal
 * @param[in]	: 	None
 * @return 		:	None
 * */
void init_gpio();
uint8_t get_button_status();
#endif /* GPIO_H_ */
