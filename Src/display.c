/*
 * display.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Parth
 */

#include "display.h"
#include "spi.h"
#include "systick.h"
/**
 * RST is active low.
 * D/nC : 1-Data 0-Command
 * BSY is active high. 1 means device is busy.
 */

void display_init() {
	display_reset();
	display_send_command(0x01);			//POWER SETTING
	display_send_data(0x03);
	display_send_data(0x00);
	display_send_data(0x2b);
	display_send_data(0x2b);

	display_send_command(0x06);         //boost soft start
	display_send_data(0x17);		//A
	display_send_data(0x17);		//B
	display_send_data(0x17);		//C

	display_send_command(0x04);
	display_busy_wait();

	display_send_command(0x00);			//panel setting
	display_send_data(0x1f);		//KW-bf   KWR-2F	BWROTP 0f	BWOTP 1f


	display_send_command(0x30);
	display_send_data(0x3c);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ

	display_send_command(0x61);			//resolution setting
	display_send_data(0x01);
	display_send_data(0x90);	 //400
	display_send_data(0x01);	 //300
	display_send_data(0x2c);

	display_send_command(0x82);			//vcom_DC setting
	display_send_data(0x12);

	display_send_command(0X50);
	display_send_data(0x97);
}
void display_reset() {
	for (int i = 0; i < 3; i++) {
		CLR_RST;
		delay_ms(50);
		SET_RST;
		delay_ms(50);
	}
}
void display_send_command(uint8_t cmd) {
	CLR_DC;
	CLR_CS;
	tx_byte(cmd);
	while (SPI_BUSY);
	SET_CS;
}

void display_send_data(uint8_t data) {
	SET_DC;
	CLR_CS;
	tx_byte(data);
	while (SPI_BUSY);
	SET_CS;
}
void display_busy_wait() {
	display_send_command(0x71);
	while (BUSY_STS == 0) {      //LOW: idle, HIGH: busy
		display_send_command(0x71);
		delay_ms(100);
	}
}

void display_clear(){
	display_send_command(0x13);
	for(int i=0;i<DISPLAY_BUFFER_SIZE;i++){
		display_send_data(0xFF);
	}
	display_send_command(0x12);
}

/**
 * Move this function somewhere else later on. Probably to render.c
 */
void display_render_image(uint8_t *imageData){
	display_send_command(0x13);
	for(int i=0;i<DISPLAY_BUFFER_SIZE;i++){
		display_send_data(~imageData[i]);
	}
	display_send_command(0x12);
}
