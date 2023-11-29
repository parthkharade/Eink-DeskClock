/*
 * uart.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Parth
 */
#include "uart.h"
/*
 * BAUD RATE = 115200.
 * PRESCALAR = 24,000,000/115200 = 2.666
 * MANTISSA = 416
 * FRACTION = .3333 ~= .3125 = (5/16)
 * FRATIONAL PART = 10
 * */

#define USART_MANTISSA	104
#define USART_FRACTION	3
void init_uart(USART_TypeDef *USART, uint32_t baud){


	RCC->APB1ENR |= (RCC_APB1ENR_USART2EN);
	USART->CR1 |= USART_CR1_TE|USART_CR1_RE;
	USART->BRR = (USART_FRACTION<<USART_BRR_DIV_Fraction_Pos) | (USART_MANTISSA<<USART_BRR_DIV_Mantissa_Pos);
	USART->CR1 |= USART_CR1_UE;
}
