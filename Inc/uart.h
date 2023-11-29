/*
 * uart.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Parth
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f411xe.h"

void init_uart(USART_TypeDef *USART, uint32_t baud);
#endif /* UART_H_ */
