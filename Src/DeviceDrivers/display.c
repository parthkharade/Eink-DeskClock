/*
 * display.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Parth
 */

#include "display.h"
#include "spi.h"
#include "systick.h"
#include "assets/icons/icons.h"
#include "render.h"
/**
 * RST is active low.
 * D/nC : 1-Data 0-Command
 * BSY is active high. 1 means device is busy.
 */


// Initialisation functions and partial luts leveraged from https://github.com/waveshareteam/e-Paper/tree/master/STM32/STM32-F103ZET6
uint16_t busy_wait_count = 0;
uint8_t display_timeout_flag = 0;
uint8_t display_timeout_count = 0;
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

static void EPD_4IN2_Partial_SetLut(void);
static void EPD_4IN2_Partial_SetLut(void)
{
	unsigned int count;
	display_send_command(0x20);
	for(count=0;count<44;count++)
		{display_send_data(EPD_4IN2_Partial_lut_vcom1[count]);}

	display_send_command(0x21);
	for(count=0;count<42;count++)
		{display_send_data(EPD_4IN2_Partial_lut_ww1[count]);}

	display_send_command(0x22);
	for(count=0;count<42;count++)
		{display_send_data(EPD_4IN2_Partial_lut_bw1[count]);}

	display_send_command(0x23);
	for(count=0;count<42;count++)
		{display_send_data(EPD_4IN2_Partial_lut_wb1[count]);}

	display_send_command(0x24);
	for(count=0;count<42;count++)
		{display_send_data(EPD_4IN2_Partial_lut_bb1[count]);}
}
void display_init() {
	display_reset();
	display_send_command(DISP_PWR);			//POWER SETTING
	display_send_data(0x03);
	display_send_data(0x00);
	display_send_data(0x2b);
	display_send_data(0x2b);

	display_send_command(DISP_BTST);         //boost soft start
	display_send_data(0x17);		//A
	display_send_data(0x17);		//B
	display_send_data(0x17);		//C

	display_send_command(DISP_PON);
	display_busy_wait();

	display_send_command(DISP_PSR);			//panel setting
	display_send_data(0x1f);		//KW-bf   KWR-2F	BWROTP 0f	BWOTP 1f


	display_send_command(DISP_PLL);
	display_send_data(0x3c);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ

	display_send_command(DISP_TRES);			//resolution setting
	display_send_data(0x01);
	display_send_data(0x90);	 //400
	display_send_data(0x01);	 //300
	display_send_data(0x2c);

	display_send_command(DISP_VDCS);			//vcom_DC setting
	display_send_data(0x12);

	display_send_command(DISP_CDI);
	display_send_data(0x97);

}
void display_init_partial() {
	display_reset();
	display_send_command(DISP_PWR);			//POWER SETTING
	display_send_data(0x03);
	display_send_data(0x00);
	display_send_data(0x2b);
	display_send_data(0x2b);

	display_send_command(DISP_BTST);         //boost soft start
	display_send_data(0x17);		//A
	display_send_data(0x17);		//B
	display_send_data(0x17);		//C

	display_send_command(DISP_PON);
	display_busy_wait();

	display_send_command(DISP_PSR);			//panel setting
	display_send_data(0xbf);		//KW-bf   KWR-2F	BWROTP 0f	BWOTP 1f


	display_send_command(DISP_PLL);
	display_send_data(0x3c);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ

	display_send_command(DISP_TRES);			//resolution setting
	display_send_data(0x01);
	display_send_data(0x90);	 //400
	display_send_data(0x01);	 //300
	display_send_data(0x2c);

	display_send_command(DISP_VDCS);			//vcom_DC setting
	display_send_data(0x12);

	display_send_command(DISP_CDI);
	display_send_data(0x97);

	EPD_4IN2_Partial_SetLut();
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
	display_send_command(DISP_FLG);
	while (BUSY_STS == 0) {      //LOW: idle, HIGH: busy
		display_send_command(DISP_FLG);
		delay_ms(100);
		busy_wait_count++;
		if(busy_wait_count>80){
			busy_wait_count = 0;
			display_timeout_flag = 1;
			display_timeout_count++;
			break;
		}
	}
	busy_wait_count = 0;

}

void display_clear(){
	display_send_command(DISP_DTM2);
	for(int i=0;i<DISPLAY_BUFFER_SIZE;i++){
		display_send_data(0xFF);
	}
	display_send_command(0x12);
}

/**
 * Move this function somewhere else later on. Probably to render.c
 */
void display_render_image(uint8_t *imageData){
	display_busy_wait();

	display_send_command(DISP_DTM1);
	for(int i=0;i<DISPLAY_BUFFER_SIZE;i++){
		display_send_data(~old_image_buffer[i]);
	}
	display_send_command(DISP_DTM2);
	for(int i=0;i<DISPLAY_BUFFER_SIZE;i++){
		display_send_data(~imageData[i]);
	}
	display_send_command(DISP_DRF);
	create_buffer_copy();
	display_busy_wait();
}
void display_render_partial_image(uint8_t *image_data,uint16_t width,uint16_t height){

	display_send_command(DISP_DTM1);
	uint8_t x_off = 29;
	uint8_t y_off = 0;
	for(int i = 0;i<height;i++){
		for(int j=0;j<width/8;j++){
//			display_send_data(~old_image_buffer[(i+y_off)*50+(j+x_off)]);
			display_send_data(0xFF);
		}
	}
	display_send_command(DISP_DTM2);
	for(int i=0;i<height;i++){
		for(int j=0;j<width/8;j++){
//			display_send_data(~image_data[i*width/8+j]);
			display_send_data(0x81);
		}
	}
	display_send_command(DISP_DRF);
	display_busy_wait();
//	delay_ms(10);
//	display_send_command(DISP_DRF);

}
void display_set_partial(uint16_t x_start,uint16_t x_end,uint16_t y_start,uint16_t y_end){
	display_busy_wait();
	display_send_command(DISP_PTL);
	x_start = x_start<<3;
	x_end = x_end<<3;
	x_end |= 0x07;
	display_send_data((uint8_t)(x_start>>8));
	display_send_data((uint8_t)(x_start&0X00FF));
	display_send_data((uint8_t)(x_end>>8));
	display_send_data((uint8_t)(x_end&0x00FF));
	display_send_data((uint8_t)(y_start>>8));
	display_send_data((uint8_t)(y_start&0xFF));
	display_send_data((uint8_t)(y_end>>8));
	display_send_data((uint8_t)(y_end&0xFF));
	display_send_data((uint8_t)(0x28));

}

void display_partial_enable(){
	display_busy_wait();
	display_send_command(DISP_PTIN);
}
void display_partial_disable(){
	display_busy_wait();
	display_send_command(DISP_PTOUT);
}
void display_refresh(){
	display_send_command(DISP_DRF);
}
