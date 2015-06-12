/*
 * MAX7221.c
 *
 * Created: 10-Jun-15
 * Author: Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License. 
 *
 */ 

#include <avr/io.h>
#include "MAX7221.h"

//MAX7221 Initialization function
void MAX7221_initDisplay(T7SegDisplay *pDisplay,uint8_t length,volatile uint8_t *CS_PORT,uint8_t CS_PIN)
{
	uint8_t digit=1;
	
	if (length>MAXDisplayLength)
		length=MAXDisplayLength;
	pDisplay->displayLen=length;
	
	pDisplay->CS_PORT=CS_PORT;
	pDisplay->CS_PIN=CS_PIN;
	
	//Define CS_PIN as output PIN
	*(pDisplay->CS_PORT-1) |= (1<<pDisplay->CS_PIN);
	
	for(;digit<=pDisplay->displayLen;digit++)
		MAX7221_setDigit(pDisplay,digit,BLANK);
	
	//Set BCD decode mode for all digits of the display
	SendData2MAX7221(pDisplay,DECODE_MODE_REG,DECODE_MODE_CODE_B_ALL_DIGITS);
	//Define display intensity
	SendData2MAX7221(pDisplay,INTENSITY_REG,0x0F);
	//Define the display length
	SendData2MAX7221(pDisplay,SCAN_LIMIT_REG,(pDisplay->displayLen)-1);
	//Set operational mode to normal
	SendData2MAX7221(pDisplay,MODE_REG,NORMAL_OPERATION_MODE);
}

void SendData2MAX7221(T7SegDisplay *pDisplay,uint8_t address, uint8_t value)
{
	// Set /CS pin low
	*(pDisplay->CS_PORT) &= ~(1<<pDisplay->CS_PIN);
	
	//Send Register Address to MAX7221
	SPI_DataSend(address);
	//Send Register Value to MAX7221
	SPI_DataSend(value);

	// Set /CS pin high 
	*(pDisplay->CS_PORT) |= (1<<pDisplay->CS_PIN);
}

//Set value of nth digit
void MAX7221_setDigit(T7SegDisplay *pDisplay,uint8_t digit,uint8_t value)
{
	if(digit<=pDisplay->displayLen)
		pDisplay->display[digit]=value;
}

//Refresh the value of a single digit
void MAX7221_refreshDigit(T7SegDisplay *pDisplay,uint8_t digit)
{
	SendData2MAX7221(pDisplay,digit,pDisplay->display[digit]);
}

//Refresh the whole display
void MAX7221_refreshDisplay(T7SegDisplay *pDisplay)
{
	uint8_t digit=1;
	
	for(;digit<=pDisplay->displayLen;digit++)
		SendData2MAX7221(pDisplay,digit,pDisplay->display[digit]);
}

//Clear display
void MAX7221_clearDisplay(T7SegDisplay *pDisplay)
{
	uint8_t digit=1;
	
	for(;digit<=pDisplay->displayLen;digit++)
		MAX7221_setDigit(pDisplay,digit,BLANK);
		
	MAX7221_refreshDisplay(pDisplay);
}

//Set display in shutdown mode
void MAX7221_shutdownDisplay(T7SegDisplay *pDisplay)
{
	SendData2MAX7221(pDisplay,MODE_REG,SHUTDOWN_MODE);
}

//Resume to normal mode of operation after entering in shutdown mode
void MAX7221_wakeUpDisplay(T7SegDisplay *pDisplay)
{
	SendData2MAX7221(pDisplay,MODE_REG,NORMAL_OPERATION_MODE);
}

//Show integer value on the display
void MAX7221_showIntNumber(T7SegDisplay *pDisplay,int32_t number)
{
	uint8_t digit;
	uint8_t position = 0;
	uint8_t sign = 0;
	
	MAX7221_clearDisplay(pDisplay);
	
	if (number<0)
	{
		sign = 1;
		number*=-1;
	}
		
	while(number && position<(pDisplay->displayLen)) 
	{
		digit=number%10;
		number/=10;
		MAX7221_setDigit(pDisplay,++position,digit);
	}
	
	if (sign)
		MAX7221_setDigit(pDisplay,++position,CHAR_MINUS);
		
	MAX7221_refreshDisplay(pDisplay);
	
	return;
}

//Send data with SPI
void SPI_DataSend(uint8_t value)
{
	// Start transmission
	SPDR = value;
	// Wait for transmission to complete
	while(!(SPSR & (1<<SPIF)));
}