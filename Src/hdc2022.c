/*
 * hdc2022.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#include "hdc2022.h"
#include "i2c.h"
#include "systick.h"
uint8_t temp_hum[2];
#define TWOPOW16 65536
void send_some_data(){
	uint8_t data[] = {0x0E};

	i2c_write_bytes(data, 0x40, 1);
}
uint16_t read_device_id(){
	uint8_t rec_buff[2];
	i2c_read_bytes(rec_buff, 0x40, 0xFE, 2);
	uint16_t dev_id = (rec_buff[0]|rec_buff[1]<<8);
	return dev_id;
}
uint8_t *hdc2022_get_data(){
	uint8_t rec_buf[4];


	hdc2022_trigger_measurement();
	delay_ms(10);
	i2c_read_bytes(rec_buf, 0x40, 0x00, 4);
	float raw_temp_hum;
	raw_temp_hum = ((rec_buf[1]<<8|rec_buf[0])*165.0/TWOPOW16 - 40);

	temp_hum[0] = (uint8_t)raw_temp_hum;

	raw_temp_hum = (rec_buf[3]<<8|rec_buf[2])*100.0/TWOPOW16;

	temp_hum[1] = (uint8_t)raw_temp_hum;

	return temp_hum;

}
void hdc2022_trigger_measurement(){
	uint8_t data_buf[2] = {0x0F,0x01};
	i2c_write_bytes(data_buf, 0x40, 2);
}
