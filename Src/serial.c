/*
 * serial.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Parth
 */
#include "serial.h"
#include "uart.h"
#define SERIAL_USART USART2
void init_serial(){
	init_uart(USART2, (uint32_t)115200);
}
char get_char(){

	char c;
	while(!(SERIAL_USART->SR&USART_SR_RXNE));
	c = SERIAL_USART->DR;
	return c;
}
void put_char(char c){
	while(!(SERIAL_USART->SR&USART_SR_TXE));
	SERIAL_USART->DR = c;

}
void put_str(char *c){
	while(*c != 0){
		put_char(*c);
		c++;
	}
}
void put_num(uint8_t num){
	char num_str[4];
	for(uint8_t i = 0;i<3;i++){
		num_str[2-i] = num%10 + 48;
		num = num/10;
	}
	for(uint8_t i = 0;i<3;i++){
		if(num_str[i] != 48 || i == 2)
			break;
		else
			num_str[i] = 32;
	}
	num_str[3] = 0;
	put_str(num_str);
}
