/*
 * display.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Parth
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "stm32f411xe.h"

 // GPIO set and Clr macros
#define SET_DC GPIOA->BSRR |= GPIO_BSRR_BS0
#define CLR_DC GPIOA->BSRR |= GPIO_BSRR_BR0

#define SET_RST GPIOA->BSRR |= GPIO_BSRR_BS2
#define CLR_RST GPIOA->BSRR |= GPIO_BSRR_BR2

#define BUSY_STS (GPIOA->IDR & (1<<3))


// Display Commands;

#define DISP_PSR 	0x00 	// Panel Setting Register
#define DISP_PWR 	0x01	// Power Setting Register
#define DISP_POF 	0x02	// Power Off
#define DISP_PFS	0x03	// Power Off Sequence Setting Register
#define DISP_PON	0x04 	// Power On
#define DISP_PMES	0x05 	// Power On Measure
#define DISP_BTST	0x06	// Booster Soft Start
#define DISP_DSLP	0x07	// Deep Sleep
#define DISP_DTM1	0x10	// Start Transmission 1
#define DISP_DSP	0x11 	// Stop Transmission
#define DISP_DRF	0x12 	// Refresh Display
#define DISP_DTM2	0x13	// Start Transmission 2
#define DISP_PLL	0x30	// PLL Control
#define DISP_TSC	0x40 	// Temp Sensor Calibration
#define DISP_TSW	0x41 	// Temp Sensor Write
#define DISP_TSE	0x42	// Temp Sensor Selection
#define DISP_TSR	0x43 	// Temp Sensor Read
#define DISP_CDI	0x50	// VCOM and data interval setting
#define DISP_LPD	0x51	// Low Power Detection
#define DISP_TCON   0x60	// TCON Setting
#define DISP_TRES   0x61	// Resolution Setting
#define DISP_GSST   0x65    // GSST Setting
#define DISP_REV    0x70    // Revision version
#define DISP_FLG    0x71    // Get Status Flag
#define DISP_AVCM   0x80    // Auto measeure Vcom
#define DISP_RVCM   0x81    // Read Vcom
#define DISP_RVCM   0x82    // VCOM DC SETTING
#define DISP_PTL    0x90    // Partial Window Setting
#define DISP_PTIN   0x91    // Parital in
#define DISP_PTOUT  0x92    // Partial Out
#define DISP_PGM    0xA0    // Program Mode
#define DISP_AGP    0xA1    // Active Programming
#define DISP_ROTP   0xA2    // Read OTP
#define DISP_CCSET  0xE0    // Cascade Setting
#define DISP_PWS    0xE3    // Power Saving
#define DISP_TSSET  0xE5    // Force Temperature.

void display_init();
void display_send_command(uint8_t cmd);
void display_send_data(uint8_t data);
void display_reset();
void display_busy_wait();
void display_render_image(uint8_t* imageData);
void display_set_lut(void);
#endif /* DISPLAY_H_ */
