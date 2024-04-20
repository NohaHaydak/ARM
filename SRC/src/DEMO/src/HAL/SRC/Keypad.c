/*
 * Keybad.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Noha
 */
#include "Error.h"
#include "STD_TYPES.h"
#include "GPIO.h"
#include "Keypad.h"


extern const KEYPAD_t KEYPAD_Configuration[NUM_OF_PINS];
extern const u8 KEYPAD_Keys[ROWS_NUM][COLS_NUM];
u8 G_swState=0;
u8 G_newPressedKey=0;
//KeypadPost_t KEYPAD_postion;

void KEYPAD_Init(void)
{
	GPIO_Config_t sw;
	sw.Speed=GPIO_SPEED_HIGH;

	for(u32 itr=0; itr<NUM_OF_PINS; itr++)
	{
		switch(KEYPAD_Configuration[itr].connection)
		{
			case CONNECTION_PU:
				sw.Mode=GPIO_MODE_INPUT_PU;
				break;
			case CONNECTION_PD:
				sw.Mode=GPIO_MODE_INPUT_PD;
				break;
			case OTPUT_NO_CONNSCTION:
				sw.Mode=GPIO_MODE_OUTPUT_PP;
				break;

			default:
				break;
		}

		sw.Port=KEYPAD_Configuration[itr].port;
		sw.Pin=KEYPAD_Configuration[itr].pin;
		GPIO_InitPin(&sw);
		}

	//setting default value of rows to be 1 (high) as they are outputs the other pullup resistors are already set to 1/
	for (int itr=0; itr<ROWS_NUM; itr++)
	{
		GPIO_SetPinValue(KEYPAD_Configuration[itr+COLS_NUM].port,KEYPAD_Configuration[itr].pin,GPIO_STATE_HIGH);
	}

}


KEYPAD_enuErrorStatus_t KEYPAD_voidGetPressedKey(u8 * Copy_pu8KeyValue)
{
	KEYPAD_enuErrorStatus_t KEYPAD_enuErrorStatus=KEYPAD_StatusOk;
	if(Copy_pu8KeyValue == NULL )
	{
		KEYPAD_enuErrorStatus=KEYPAD_StatusNOk;
	}
	if(G_newPressedKey==1&&G_swState!=0)
	{
		* Copy_pu8KeyValue=G_swState;
		G_newPressedKey=0;
	}
	else
	{
		* Copy_pu8KeyValue=0;
	}
		
	return KEYPAD_enuErrorStatus;
}
/*KEYPAD_enuErrorStatus_t KEYPAD_voidGetPressedKey(u8 * Copy_pu8KeyValue)
{
	KEYPAD_enuErrorStatus_t KEYPAD_enuErrorStatus=KEYPAD_StatusOk;
	if(Copy_pu8KeyValue == NULL)
	{
		KEYPAD_enuErrorStatus=KEYPAD_StatusNOk;
	}
	else
	{
		* Copy_pu8KeyValue=G_swState;
	}
	return KEYPAD_enuErrorStatus;
}
*/
void KEYPADGetKey_Runnable(void)

{
	u8 Loc_swcurrent=0;
	u8 Loc_swState=0;
	//static u32 Loc_swPrev[ROWS_NUM][COLS_NUM]={0};
	static u32  Loc_swCounts[ROWS_NUM][COLS_NUM]={0};

	for (u8 itr1=0; itr1<ROWS_NUM &&Loc_swState==0; itr1++)
	{
		GPIO_SetPinValue(KEYPAD_Configuration[itr1+COLS_NUM].port,KEYPAD_Configuration[itr1+COLS_NUM].pin,GPIO_STATE_LOW);
		//col->i/p
		
		for (u8 itr2=0; itr2<COLS_NUM &&Loc_swState==0; itr2++)
		{
			GPIO_GetPinValue(KEYPAD_Configuration[itr2].port,KEYPAD_Configuration[itr2].pin,&Loc_swcurrent);

			if(Loc_swcurrent==GPIO_STATE_LOW)
			{
				Loc_swCounts[itr1][itr2]++;
			}
			else
			{
				Loc_swCounts[itr1][itr2]=0;
			}
			if(Loc_swCounts[itr1][itr2]==5)
			{
				Loc_swState=KEYPAD_Keys[itr1][itr2];
				Loc_swCounts[itr1][itr2]=0;
				//Loc_swcurrent=0;
			}
			if(Loc_swState!=G_swState)
			{
				G_swState=Loc_swState;
				G_newPressedKey=1;

			}
		
			//Loc_swPrev[itr1][itr2]=Loc_swcurrent;

		}
		
		GPIO_SetPinValue(KEYPAD_Configuration[itr1+COLS_NUM].port,KEYPAD_Configuration[itr1+COLS_NUM].pin,GPIO_STATE_HIGH);

	}

}