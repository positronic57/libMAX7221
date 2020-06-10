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
#include <util/delay.h>

#include "MAX7221.h"

void SPI_Master_Init();

int main(void)
{
	T7SegDisplay SevenSegDisplay;

	// Init SPI hardware as master.
	SPI_Master_Init();
	
	// Init one raw 7Seg Display driven by MAX7221
	MAX7221_initDisplay(&SevenSegDisplay, 5, &PORTB,PORTB2);
	MAX7221_refreshDisplay(&SevenSegDisplay);

	// Set the value for DIGIT5 in the display buffer.	
	MAX7221_setDigit(&SevenSegDisplay, DIGIT5, CHAR_MINUS);

	// Set the value for DIGIT4 in the display buffer.	
	MAX7221_setDigit(&SevenSegDisplay, DIGIT4, 8);

	// Set the value for DIGIT3 in the display buffer.	
	MAX7221_setDigit(&SevenSegDisplay, DIGIT3, (0x02|DECIMAL_POINT));

	// Set the value for DIGIT2 in the display buffer.	
	MAX7221_setDigit(&SevenSegDisplay,DIGIT2,1);

	// Set the value for DIGIT1 in the display buffer.	
	MAX7221_setDigit(&SevenSegDisplay,DIGIT1,5);

	//Display the content of the buffer on the dispaly module
	MAX7221_refreshDisplay(&SevenSegDisplay);
	
    while(1){
        _delay_ms(500);
    }
	
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
