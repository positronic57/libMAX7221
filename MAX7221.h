/**
 * @file MAX7221.h
 * @brief 
 * Header file of MAX7221 library. It contains the prototypes of all
 * functions available in the library, definitions of all macros
 * and constans.
 * 
 * @author Goce Boshkovski
 * @date 10-Jun-15
 * @copyright GNU General Public License v2.
 * 
 */
#include <stdint.h>

#ifndef MAX7221_H_
#define MAX7221_H_

/** \defgroup regAddr Addresses of MAX7221 digit registers */
/* @{ */
#define DIGIT1 0x01
#define DIGIT2 0x02
#define DIGIT3 0x03
#define DIGIT4 0x04
#define DIGIT5 0x05
#define DIGIT6 0x06
#define DIGIT7 0x07
#define DIGIT8 0x08
/* @} */

/** \defgroup regCont Addresses of MAX7221 control registers */
/* @{ */
#define DECODE_MODE_REG 0x09
#define INTENSITY_REG 0x0A
#define MODE_REG 0x0C
#define SCAN_LIMIT_REG 0x0B
#define DISP_TEST_REG 0x0F
/* @} */

/** \defgroup decode MAX7221 decode modes */
/* @{ */
#define DECODE_MODE_NO_DEC 0x00
#define DECODE_MODE_CODE_B_DIGIT0 0x01
#define DECODE_MODE_CODE_B_DIGIT0_DIGIT3 0x0F
#define DECODE_MODE_CODE_B_ALL_DIGITS 0xFF
/* @} */

/** \defgroup ops MAX7221 modes of operation */
/* @{ */
#define SHUTDOWN_MODE 0x00
#define NORMAL_OPERATION_MODE 0x01
/* @} */

/** \defgroup chars Special Characters */
/* @{ */
#define DECIMAL_POINT 0x80
#define CHAR_MINUS 0x0A
#define CHAR_E 0x0B
#define CHAR_H 0x0C
#define CHAR_L 0x0D
#define CHAR_P 0x0E
#define BLANK 0x0F
/* @} */

/** \defgroup brightness Values for digital control of display brightness */
/* @{ */
#define DIM 0x02	// 3/16 of the Iset
#define BRIGHT 0x07	// 8/16 of the Iset
#define MAX_BRIGHTNESS 0x0F	// 15/16 of the Iset 
/* @} */

/**
 * @brief Defines the maximum length of the display expressed as number of 7seg LEDs.
 * 
 */
#define MAXDisplayLength 0x08

/** \defgroup libMacros MAX7221 library macros */
/* @{ */

/**
 * @brief Resume to normal mode of operation from shutdown mode
 * where pDisplay is a pointer to the structure that represents the display.
 */
#define MAX7221_wakeUpDisplay(pDisplay)	SendData2MAX7221(pDisplay,MODE_REG,NORMAL_OPERATION_MODE)
/**
 * @brief Puts the 7Seg display in shutdown mode
 * where pDisplay is a pointer to the structure that represents the display.
 */
#define MAX7221_shutdownDisplay(pDisplay) SendData2MAX7221(pDisplay,MODE_REG,SHUTDOWN_MODE)
/* @} */

/**
 * @brief Digital control of display brightness.
 * Sets display intensity/brightness.
 * where pDisplay pointer to the structure that represents the display
 * and level is the brightness level.
 */
#define MAX7221_SetDispalyIntensity(pDisplay,level) SendData2MAX7221(pDisplay,INTENSITY_REG,level)
/* @} */

/**
 * @brief MAX7221 7SegDisplay is represented by this structure.
 */
typedef struct S7SegDisplay 
{
	uint8_t display[MAXDisplayLength+1]; /**< display buffer. The content of this buffer is presented on the display.*/
	uint8_t displayLen; /**< number of 7seg LEDs in the display.*/
	volatile uint8_t *CS_PORT; /**< pointer to the MCU PORT that holds the SPI CS pin.*/
	uint8_t CS_PIN; /**< MCU PIN connected to the CS pin of MAX7221*/
} T7SegDisplay;

/** \defgroup libFunctions MAX7221 library functions */
/* @{ */
/**
 * @brief The function is used to initilaze the MAX7221 driver by configuring 
 * all of the relevant MAX7221 parameters and set the CS PIN as output one. 
 * 
 * By defualt, the init function puts MAX7221 in normal mode of operation 
 * with decode mode set to DECODE_MODE_CODE_B_ALL_DIGITS and
 * display intensity set to maximum. Those values can be changed later in the
 * code by using SendData2MAX7221() function.
 * 
 * @param[in,out] pDisplay pointer to the structure that represent MAX7221
 * @param[in] length is the number of 7Seg LEDs in the display. Maximum value is 8. 
 * @param[in] CS_PORT is a pointer to the MCU PORT that holds the CS pin for MAX7221
 * @param[in] CS_PIN MCU pin connected to the CS pin of MAX7221
 * @return void.
 */
void MAX7221_initDisplay(T7SegDisplay *pDisplay,uint8_t length,volatile uint8_t *CS_PORT,uint8_t CS_PIN);

/**
 * @brief Updates the content of a specific MAX7221 register.
 * 
 * @param[in] pDisplay pointer to the structure that represents the display.
 * @param[in] address is the address of the MAX7221 register.
 * @param[in] value is the new value of the MAX7221 register.
 *  
 * @return void.
 */
void SendData2MAX7221(T7SegDisplay *pDisplay,uint8_t address,uint8_t value);

/**
 * @brief Sets the value of the n-th digit in the display buffer defined in 7SegDispaly structure.
 * 
 * @param[in] pDisplay pointer to the structure that represents the display.
 * @param[in] digit position of the digit in the display where 1<= digit <=displayLen.
 * @param[in] value is the value to be displayed.
 *  
 * @return void.
 */
void MAX7221_setDigit(T7SegDisplay *pDisplay,uint8_t digit,uint8_t value);

/**
 * @brief Refreshes the content of the n-th 7Seg LED using the 
 * coresponding value from the display buffer.
 * 
 * @param[in] pDisplay pointer to the structure that represents the display.
 * @param[in] digit digit number where 1<= digit <=displayLen.
 * @return void.
 */
void MAX7221_refreshDigit(T7SegDisplay *pDisplay,uint8_t digit);

/**
 * @brief Diplays the content of the buffer on the displays.
 * 
 * @param[in] pDisplay pointer to the structure that represents the display.
 * @return void.
 */
void MAX7221_refreshDisplay(T7SegDisplay *pDisplay);

/**
 * @brief Blanks the 7Seg Display.
 * 
 * @param[in] pDisplay pointer to the structure that represents the display.
 *  
 * @return void.
 */
void MAX7221_clearDisplay(T7SegDisplay *pDisplay);

/**
 * @brief Displays integer value on the display.
 * 
 * @param[in] pDisplay pointer to the structure that represents the display.
 * @param[in] number integer value to display.
 *  
 * @return void.
 */
void MAX7221_showIntNumber(T7SegDisplay *pDisplay,int32_t number);

/**
 * @brief Sends data to MAX7221 via SPI.
 * 
 * @param[in] value data value to be send via SPI.
 *  
 * @return void.
 */
void SPI_DataSend(uint8_t value);
/* @} */
#endif /* MAX7221_H_ */

