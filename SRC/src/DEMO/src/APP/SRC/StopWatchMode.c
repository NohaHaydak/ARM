/*
 * StopWatchMode.c
 *
 *  Created on: Apr 7, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "Error.h"
#include "STD_TYPES.h"
#include "GPIO.h"
#include "LCD_CFG.h"
#include "LCD.h"
#include "Mode.h"
#include "StopWatch.h"

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

#define PERIODICITY 50
#define FIRST_ROW 0
#define SECOND_ROW 1
#define STRING_COLUMN 1
#define NUMBERS_COLUMN 5
#define MODE_OFF 0
#define MODE_ON 1
#define MODE_RESET 2
#define MAX_MSEC 100
#define MAX_SEC 60

/****************************************************************************************
 *                        	            Variables                                     *
 ****************************************************************************************/

extern SelectMode_t G_enuMode;
extern StopWatchControl_t G_enuStopWatchControl;

/****************************************************************************************
 *                        	              Runnable Implementation                    *
 ****************************************************************************************/
/**
 *@brief  : Control the stopwatch.
 *@periodicity:
 */
void StopWatchMode_Runnable(void) ////50 msec
{
	static u32 Loc_mSec=0;
	static u32 Loc_Sec=0;
	static u32 Loc_Min=0;
	static u32 Loc_Mode=MODE_OFF;

	/*Check if stop watch mode is on then display it on the LCD*/
	if(G_enuMode == StopWatch_Mode)
	{
		LCD_ClearScreenAsynch();
		LCD_SetCursorPositionAsynch(FIRST_ROW,STRING_COLUMN);
		LCD_WriteStringAsynch("StopWatch Mode");

		if(Loc_Min < 10)
		{
			LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN);
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(Loc_Min);
		}
		else if(Loc_Min > 99)
		{
			LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN-1);
			LCD_WriteNumberAsynch(Loc_Min);
		}
		else
		{
			LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN);
			LCD_WriteNumberAsynch(Loc_Min);
		}

		LCD_WriteStringAsynch(".");

		if(Loc_Sec < 10)
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(Loc_Sec);
		}
		else
		{
			LCD_WriteNumberAsynch(Loc_Sec);
		}

		LCD_WriteStringAsynch(".");
		if(Loc_mSec < 10)
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(Loc_mSec);
		}
		else
		{
			LCD_WriteNumberAsynch(Loc_mSec);
		}

		switch(G_enuStopWatchControl)
		{
		case StopWatch_On:
			Loc_Mode = MODE_ON;
			break;

		case StopWatch_Pause:
			Loc_Mode = MODE_OFF;
			break;

		case StopWatch_Reset:
			Loc_Mode = MODE_RESET;
			break;

		case No_Action:
			break;

		default:
			break;
		}


	}

	/*Increment the numbers*/
	if(Loc_Mode == MODE_ON)
	{
		Loc_mSec+=PERIODICITY;

		if(Loc_mSec == MAX_MSEC)
		{
			Loc_mSec=0;
			Loc_Sec++;
		}
		if(Loc_Sec == MAX_SEC)
		{
			Loc_Sec=0;
			Loc_Min++;
		}
	}
	/*Reset the numbers and display zeroes on LCD*/
	else if(Loc_Mode == MODE_RESET)
	{
		Loc_mSec=0;
		Loc_Sec=0;
		Loc_Min=0;
		LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN);
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(0);
		LCD_WriteStringAsynch(".");
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(0);
		LCD_WriteStringAsynch(".");
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(0);
		Loc_Mode = MODE_OFF;
	}
	else
	{

	}

}
