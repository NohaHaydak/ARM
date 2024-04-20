/*
 * ReceiveData.c
 *
 *  Created on: Apr 7, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "Error.h"
#include "STD_TYPES.h"
#include "USART.h"
#include "GPIO.h"
#include "HUSART.h"
#include "Mode.h"
#include "Edit.h"
#include "StopWatch.h"


/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

#define PAUSE 2
#define STOPWATCH_ON 1

/****************************************************************************************
 *                        	            Variables                                     *
 ****************************************************************************************/

EditState_t G_enuEditMode=Edit_OFF;
SelectMode_t G_enuMode= Display_Mode;
EditPressedButton_t G_enuEditControl= No_Edit_Action;
StopWatchControl_t G_enuStopWatchControl=No_Action;
/****************************************************************************************
 *                        	              Runnable Implementation                   *
 ****************************************************************************************/

/**
 *@brief  : Receive the pressed key over UART and update states.
 *@periodicity:
 */
void ReceiveData_Runnable(void)
{
	u8 Loc_Key;
	HUSART_ReceiveByte(USART1,&Loc_Key);

	static u8 Loc_StopWatchCount=STOPWATCH_ON;
	switch(Loc_Key)
	{
	/*Change mode*/
	case 'M':
		G_enuMode ^=1;
		break;

		/*Start/Pause/Continue stopwatch*/
	case 'S':
		if(G_enuMode == StopWatch_Mode)
		{
			switch(Loc_StopWatchCount)
			{
			/*Start stopwatch*/
			case STOPWATCH_ON:
				G_enuStopWatchControl = StopWatch_On;
				Loc_StopWatchCount = PAUSE;
				break;

				/*Pause stopwatch*/
			case PAUSE:
				G_enuStopWatchControl = StopWatch_Pause;
				Loc_StopWatchCount =STOPWATCH_ON;
				break;

			default:
				break;
			}

		}
		break;

		/*Reset stopwatch*/
	case 'C':
		if(G_enuMode == StopWatch_Mode)
		{
			G_enuStopWatchControl = StopWatch_Reset;
			Loc_StopWatchCount = STOPWATCH_ON;

		}
		break;

		/*Edit date or time*/
	case 'E':
		if(G_enuMode == Display_Mode)
		{
			G_enuEditMode=Edit_ON;
		}
		break;

		/*Confirm edit*/
	case 'K':
		if(G_enuMode == Display_Mode && G_enuEditMode==Edit_ON)
		{
			G_enuEditControl=Edit_Ok;
		}
		break;

		/*Go to the first row*/
	case 'U':
		if(G_enuMode == Display_Mode && G_enuEditMode==Edit_ON)
		{
			G_enuEditControl=Up_Arrow;
		}
		break;

		/*Go to the second row*/
	case 'D':
		if(G_enuMode == Display_Mode && G_enuEditMode==Edit_ON)
		{
			G_enuEditControl=Down_Arrow;
		}
		break;

		/*Go left*/
	case 'L':
		if(G_enuMode == Display_Mode && G_enuEditMode==Edit_ON)
		{
			G_enuEditControl=Left_Arrow;
		}
		break;

		/*Go right*/
	case 'R':
		if(G_enuMode == Display_Mode && G_enuEditMode==Edit_ON)
		{
			G_enuEditControl=Right_Arrow;
		}
		break;

		/*Increase the selected number*/
	case '+':
		if(G_enuMode == Display_Mode && G_enuEditMode==Edit_ON)
		{
			G_enuEditControl=Increase_Button;
		}
		break;

		/*Decrease the selected number*/
	case '-':
		if(G_enuMode == Display_Mode && G_enuEditMode==Edit_ON)
		{
			G_enuEditControl=Decrease_Button;
		}
	    break;

	default:
		break;

	}
}


