### AVR C Library for MAX7221

#### Short Description

LibMAX7221 is a C library for AVR 8-bit microcontrollers for 7-Seg display driven by MAX7221.

#### Supported MCU Hardware and 7-Seg Display modules

The library is compatible with every 8-bit AVR microcontroller which has SPI that supports standard SPI master
mode with 4 wires for SPI physical bus.

It supports only a single raw 7-Seg Display with maximum 8 7Seg LEDs driven by a single MAX7221.

#### Installation

Check the instructions described in INSTALL document.

#### Usage

First the SPI module of the AVR microcontroller must be configured as standard SPI master with 4 wire SPI bus. 
Because the different AVR MCU have different PINs assigned to the SPI module, its initialization must be performed additionally and it is not done by this library.
(See the example section how to init SPI of Atmega328.)

Next step is to initialize the connected 7Seg display using the MAX7221_initDisplay() function. 
For example, if the /SS pin of MAX7221 is connected to the PB2 PIN of the MCU, the init function for display with 5 7Seg digits is:

	MAX7221_initDisplay(p7SegDisplay,5,&PORTB,PORTB2);

where: p7SegDispaly is a pointer to S7SegDisplay structure that represents the display, 5 is the lenght of the display and last two arguments define the PIN used as /SS.

The display module in the library is defined as an array of digits, where each field from the array is equivalent to one 7SEG digit.
MAX7221_setDigit() function sets the value of n-th digit in the array, while MAX7221_refreshDigit() function displays that value on the module.

For example:

	MAX7221_setDigit(p7SegDisplay,DIGIT4,8); 	//The value of the 4-th filed in the array is set to 8
	MAX7221_refreshDigit(p7SegDisplay,DIGIT4); 	//DIGIT4 from the display module is updated with the content of the 4-th filed in the array


MAX7221_refreshDisplay() presents the content of the whole array on the display module.

#### Doc

A detailed description of the library is located in the doc folder.

#### Test Hardware

Tested on Atmel Atmega328 MCU.


**WARNING:** 
The source is provided as it is without any warranty. Use it on your own risk!
The author does not take any responsibility for the damage caused while using this software.

