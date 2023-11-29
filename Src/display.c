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

static const unsigned char EPD_4IN2_lut_vcom0[] = {
    0x00, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x00, 0x0F, 0x0F, 0x00, 0x00, 0x01,
	0x00, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
	};
static const unsigned char EPD_4IN2_lut_ww[] = {
	0x50, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x90, 0x0F, 0x0F, 0x00, 0x00, 0x01,
	0xA0, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
static const unsigned char EPD_4IN2_lut_bw[] = {
	0x50, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x90, 0x0F, 0x0F, 0x00, 0x00, 0x01,
	0xA0, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
static const unsigned char EPD_4IN2_lut_wb[] = {
	0xA0, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x90, 0x0F, 0x0F, 0x00, 0x00, 0x01,
	0x50, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
static const unsigned char EPD_4IN2_lut_bb[] = {
	0x20, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x90, 0x0F, 0x0F, 0x00, 0x00, 0x01,
	0x10, 0x08, 0x08, 0x00, 0x00, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};

/******************************partial screen update LUT*********************************/
const unsigned char EPD_4IN2_Partial_lut_vcom1[] ={
    0x00, 0x01, 0x20, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char EPD_4IN2_Partial_lut_ww1[] ={
    0x00, 0x01, 0x20, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char EPD_4IN2_Partial_lut_bw1[] ={
    0x20, 0x01, 0x20, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char EPD_4IN2_Partial_lut_wb1[] ={
    0x10, 0x01, 0x20, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char EPD_4IN2_Partial_lut_bb1[] ={
    0x00, 0x01,0x20, 0x01, 0x00, 0x01,
    0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,0x00, 0x00, 0x00, 0x00,
};
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
//	display_set_lut();
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
void display_render_image(uint8_t *imageData){
	display_send_command(0x13);
	for(int i=0;i<15000;i++){
		display_send_data(imageData[i]);
	}

	display_send_command(0x12);
}

 void display_set_lut(void)
{
	unsigned int count;
	display_send_command(0x20);
	for(count=0;count<36;count++)
		{display_send_data(EPD_4IN2_lut_vcom0[count]);}

	display_send_command(0x21);
	for(count=0;count<36;count++)
		{display_send_data(EPD_4IN2_lut_ww[count]);}

	display_send_command(0x22);
	for(count=0;count<36;count++)
		{display_send_data(EPD_4IN2_lut_bw[count]);}

	display_send_command(0x23);
	for(count=0;count<36;count++)
		{display_send_data(EPD_4IN2_lut_wb[count]);}

	display_send_command(0x24);
	for(count=0;count<36;count++)
		{display_send_data(EPD_4IN2_lut_bb[count]);}
}
