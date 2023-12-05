/*
 * hdc2022.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Parth
 */

#include "hdc2022.h"



#include "i2c.h"

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
