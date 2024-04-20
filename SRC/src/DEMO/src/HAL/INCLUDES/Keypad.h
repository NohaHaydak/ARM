/*
 * Keypad.h
 *
 *  Created on: Apr 7, 2024
 *      Author: Noha
 */

#ifndef HAL_INCLUDES_KEYPAD_H_
#define HAL_INCLUDES_KEYPAD_H_

#include "GPIO.h"

#define KEYPAD_COL1 0
#define KEYPAD_COL2 1
#define KEYPAD_COL3 2
#define KEYPAD_COL4 3
#define KEYPAD_ROW1 4
//#define KEYPAD_ROW2 4
#define KEYPAD_ROW3 5
#define KEYPAD_ROW4 6


#define CONNECTION_PU 1
#define CONNECTION_PD 0
#define OTPUT_NO_CONNSCTION 2

#define SWITCH_PRESSED 1
#define SWITCH_NOT_PRESSED 0

#define ROWS_NUM 3
#define COLS_NUM 4

#define  NUM_OF_PINS 7

typedef enum
{
	KEYPAD_StatusOk,
	KEYPAD_StatusNOk

}KEYPAD_enuErrorStatus_t;


typedef struct
{
	void* port;
	u32 pin;
	/*PULL UP OR DOWN*/
	u32 connection;
}KEYPAD_t;

//void KEYPADGetKey_Runnable(void);
KEYPAD_enuErrorStatus_t KEYPAD_voidGetPressedKey(u8 * Copy_pu8KeyValue);
void KEYPAD_Init(void);
#endif /* HAL_INCLUDES_KEYPAD_H_ */
