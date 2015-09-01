/*
 * libMAX7221.c
 *
 * Created: 10-Jun-15
 * Author: Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Example of using MAX7221 library on Atmega328 for
 * one raw 7Seg display with MAX7221 driver.
 * 
 * PIN5 from PORTB is connected to the /SS pin of MAX7221.
 */

#include <avr/io.h>
#include "MAX7221.h"

void SPI_Master_Init();

int main(void)
{
	T7SegDisplay SevenSegDisplay;
	T7SegDisplay *p7SegDisplay = &SevenSegDisplay;

	// Init SPI hardware as master.
	SPI_Master_Init();
	
	// Init one raw 7Seg Display driven by MAX7221
	MAX7221_initDisplay(p7SegDisplay,5,&PORTB,PORTB2);
	
	//Example for showing integer number
	MAX7221_showIntNumber(p7SegDisplay,-7169);
	
	while(1);
	
	return 0;
}


//Init Atmega328p as SPI Master
void SPI_Master_Init()
{
	/* Set MOSI, SCK as output pins
	  /SS pin will be set as output by the MAX7221_init function
	*/
	DDRB = (1<<PORTB3)|(1<<PORTB5);
	
	/*Set SPI parameters via SPCR:
		- frequency f/16;
		- Define the microcontroller as SPI Master;
		- MSB is transmited first;
		- SCK is low when idle;
		- SPI is enable.
	*/
	SPCR = (1 << MSTR) | (1 << SPE) | (1 << SPR0);
}
