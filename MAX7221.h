/*
 * MAX7221.h
 *
 * Created: 10-Jun-15
 * Author: Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License. 
 *
 */ 

#include <stdint.h>

#ifndef MAX7221_H_
#define MAX7221_H_

//Addresses of the digit registers
#define DIGIT1 0x01
#define DIGIT2 0x02
#define DIGIT3 0x03
#define DIGIT4 0x04
#define DIGIT5 0x05
#define DIGIT6 0x06
#define DIGIT7 0x07
#define DIGIT8 0x08

//Address of the registers
#define DECODE_MODE_REG 0x09
#define INTENSITY_REG 0x0A
#define MODE_REG 0x0C
#define SCAN_LIMIT_REG 0x0B
#define DISP_TEST_REG 0x0F

//Decode mode
#define DECODE_MODE_NO_DEC 0x00
#define DECODE_MODE_CODE_B_DIGIT0 0x01
#define DECODE_MODE_CODE_B_DIGIT0_DIGIT3 0x0F
#define DECODE_MODE_CODE_B_ALL_DIGITS 0xFF

//Mode of operation
#define SHUTDOWN_MODE 0x00
#define NORMAL_OPERATION_MODE 0x01

//7-Seg Display Characters
#define DECIMAL_POINT 0x80
#define CHAR_MINUS 0x0A
#define CHAR_E 0x0B
#define CHAR_H 0x0C
#define CHAR_L 0x0D
#define CHAR_P 0x0E
#define BLANK 0x0F

#define MAXDisplayLength 0x08

typedef struct S7SegDisplay 
{
	uint8_t display[MAXDisplayLength+1];
	uint8_t displayLen;
	volatile uint8_t *CS_PORT;
	uint8_t CS_PIN;
} T7SegDisplay;

//MAX7221 Initialization function
void MAX7221_initDisplay(T7SegDisplay *pDisplay,uint8_t length,volatile uint8_t *CS_PORT,uint8_t CS_PIN);

//Send address and data to the MAX7221
void SendData2MAX7221(T7SegDisplay *,uint8_t,uint8_t);

//Set value of n-th digit
void MAX7221_setDigit(T7SegDisplay *,uint8_t,uint8_t);

//Refresh the value of a single digit
void MAX7221_refreshDigit(T7SegDisplay *,uint8_t);

//Refresh the whole display
void MAX7221_refreshDisplay(T7SegDisplay *);

//Clear the 7Seg display
void MAX7221_clearDisplay(T7SegDisplay *);

//Put the 7Seg display in shutdown mode
void MAX7221_shutdownDisplay(T7SegDisplay *);

//Resume to normal mode of operation after entering in shutdown mode
void MAX7221_wakeUpDisplay(T7SegDisplay *);

//Show integer value on the display
void MAX7221_showIntNumber(T7SegDisplay *,int32_t);

//Send data with SPI
void SPI_DataSend(uint8_t);

#endif /* MAX7221_H_ */

