/*
 * adc.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Parth
 */
#include "adc.h"
#include "stdbool.h"
#define CYCLES_56 0b011
#define CHANNEL_DACA 1
#define CHANNEL_DACB 2
volatile uint8_t result_ready = false;
volatile adc_int_count = 0;
void init_adc(){
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	ADC1->CR1 |= (2<<ADC_CR1_RES_Pos)|ADC_CR1_EOCIE;
	//Channel 1 is PA1
	ADC1->SMPR2 |= (CYCLES_56<<ADC_SMPR2_SMP1_Pos);
	ADC1->SQR3 |= (CHANNEL_DACA << ADC_SQR3_SQ1_Pos);

	NVIC_EnableIRQ(ADC_IRQn);
	ADC1->CR2 |= ADC_CR2_ADON;
}
uint8_t get_result(){
	uint16_t volt = 0;
	volt = ADC1->DR;
	result_ready = false;
	ADC1->CR2 |= ADC_CR2_SWSTART; // Start a new conversion.
	return volt;
}
/**
 * ADC IRQ Handler.
 * */
void ADC_IRQHandler(){
	adc_int_count++;
	result_ready = true;
	ADC1->SR &= ~(ADC_SR_EOC);
	NVIC_ClearPendingIRQ(ADC_IRQn);
}
