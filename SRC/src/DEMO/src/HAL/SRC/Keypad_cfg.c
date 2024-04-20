/*
 * Keypad_cfg.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Noha
 */

#include "Error.h"
#include "STD_TYPES.h"
#include "GPIO.h"
#include "Keypad.h"



KEYPAD_t KEYPAD_Configuration[NUM_OF_PINS]=
{
		[KEYPAD_COL4]={.port=GPIO_PORTB, .pin=GPIO_PIN0, .connection=CONNECTION_PU},
		[KEYPAD_COL3]={.port=GPIO_PORTB, .pin=GPIO_PIN1, .connection=CONNECTION_PU},
		[KEYPAD_COL2]={.port=GPIO_PORTB, .pin=GPIO_PIN3, .connection=CONNECTION_PU},
		[KEYPAD_COL1]={.port=GPIO_PORTB, .pin=GPIO_PIN4, .connection=CONNECTION_PU},
		[KEYPAD_ROW1]={.port=GPIO_PORTB, .pin=GPIO_PIN5, .connection=OTPUT_NO_CONNSCTION},
		//[KEYPAD_ROW2]={.port=GPIO_PORTB, .pin=GPIO_PIN12, .connection=OTPUT_NO_CONNSCTION},
		[KEYPAD_ROW3]={.port=GPIO_PORTB, .pin=GPIO_PIN6, .connection=OTPUT_NO_CONNSCTION},
		[KEYPAD_ROW4]={.port=GPIO_PORTB, .pin=GPIO_PIN7,.connection=OTPUT_NO_CONNSCTION}
};


u8 KEYPAD_Keys[ROWS_NUM][COLS_NUM]=
{


		{'M','S','C','E'},
		//edit ok increase
		//{'E','K','+'},
		// up decrease
		{'x','U','K','+'},
		//left down right
		{'L','D','R','-'}

};



