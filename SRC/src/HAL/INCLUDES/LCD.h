/*
 * LCD.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Noha
 */

#ifndef HAL_INCLUDES_LCD_H_
#define HAL_INCLUDES_LCD_H_

#include <stdio.h>
#include "../../LIB/std_types.h"
#include "LCD_cfg.h"

#define LCD_WRITE 0
#define LCD_READ 1
#define LCD_RS_COMMAND 0
#define LCD_RS_DATA 1
#define LCD_RS 0
#define LCD_RW 1


#define LCD_DISABLED 0
#define LCD_ENABLED  1

#define LCD_DB0 0
#define LCD_DB1 1
#define LCD_DB2 2
#define LCD_DB3 3
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7

/*.................8 bit, 2 lines in display , font 5x7..........*/
#define FUNCTION_SET_2LINE_5X7F 0b00111000
/*.................8 bit, 2 lines in display , font 5x10..........*/
#define FUNCTION_SET_2LINE_5X10F 0b00111100
/*.................8 bit, 1 lines in display , font 5x7..........*/
#define FUNCTION_SET_1LINE_5X7F 0b00110000
/*.................8 bit, 1 lines in display , font 5x10..........*/
#define FUNCTION_SET_1LINE_5X10F 0b00110100


/*.................4 bit, 2 lines in display , font 5x7..........*/
#define FOUR_BIT_FUNCTION_SET_2LINE_5X7F  0b00101000
/*.................4 bit, 2 lines in display , font 5x10..........*/
#define FOUR_BIT_FUNCTION_SET_2LINE_5X10F 0b00101100
/*.................4 bit, 1 lines in display , font 5x7..........*/
#define FOUR_BIT_FUNCTION_SET_1LINE_5X7F  0b00100000
/*.................4 bit, 1 lines in display , font 5x10..........*/
#define FOUR_BIT_FUNCTION_SET_1LINE_5X10F 0b00100100




/*.....................................................display on/off control..........................................................*/

#define DISPLAY_CURSOR_BLINK_ALL_ON 0b00001111
#define DISPLAY_CURSOR_ON_BLINK_OFF 0b00001110
#define DISPLAY_ON_CURSOR_OFF 0b00001100
#define DISPLAY_ALL_OFF 0b00001000

/*................................................................display clear.......................................................*/

#define DISPLAY_CLEAR 0b00000001



/*.............................................................Entry mode set.........................................................*/


#define ENTRY_TO_THE_RIGHT_SHIFT_ON 0b00000111
#define ENTRY_TO_THE_RIGHT_SHIFT_OFF 0b00000110

#define ENTRY_TO_THE_LEFT_SHIFT_ON 0b00000101
#define ENTRY_TO_THE_LEFT_SHIFT_OFF 0b00000100

/*.............................................................goto xy func.........................................................*/
/* second row start address */
#define SEC_ROW_START 0x40

/* set address mask by setting bit 7 by 1 to send command to DDRAM */
#define SET_AC_MASK 0b10000000

/*.........................................................shift cursor.............................................................*/
#define SHIFT_CURSOR_RIGHT         0b00010100
#define SHIFT_CURSOR_LEFT          0b00010000
#define SHIFT_ENTIER_DISPLAY_RIGHT 0b00011100
#define SHIFT_ENTIER_DISPLAY_LEFT  0b00011000


#define CGRAM_FIRST_LOCATION_COMMAND   (0x00|0b01000000)
#define CGRAM_SECOND_LOCATION_COMMAND  (0x08|0b01000000)
#define CGRAM_THIRD_LOCATION_COMMAND   (0x10|0b01000000)
#define CGRAM_FOURTH_LOCATION_COMMAND  (0x18|0b01000000)
#define CGRAM_FIFTH_LOCATION_COMMAND   (0x20|0b01000000)
#define CGRAM_SIXTH_LOCATION_COMMAND   (0x28|0b01000000)
#define CGRAM_SEVENTH_LOCATION_COMMAND (0x30|0b01000000)
#define CGRAM_EIGHTH_LOCATION_COMMAND  (0x38|0b01000000)


#define LCD_CGRAM_FIRST_LOCATION   0
#define LCD_CGRAM_SECOND_LOCATION  1
#define LCD_CGRAM_THIRD_LOCATION   2
#define LCD_CGRAM_FOURTH_LOCATION  3
#define LCD_CGRAM_FIFTH_LOCATION   4
#define LCD_CGRAM_SIXTH_LOCATION   5
#define LCD_CGRAM_SEVENTH_LOCATION 6
#define LCD_CGRAM_EIGHTH_LOCATION  7


#define CONTROL_PINS 3

#define LDC_DATA_PINS 8


void LCD_Init(void);
void LCD_task(void);
void LCD_WriteString_Asynch(char* Copy_pchPattern );
void LCD_enuGotoDDRAM_XY_Asynch(u8 Copy_u8Row, u8 Copy_u8Col);
void LCD_ClrScreen_Asynch(void);

#endif /* HAL_INCLUDES_LCD_H_ */
