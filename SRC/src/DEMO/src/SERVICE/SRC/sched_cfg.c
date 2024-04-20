/*
 * sched_cfg.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#include "sched_cfg.h"

extern void LCD_Task(void);
extern void KEYPADGetKey_Runnable(void);
extern void SendData_Runnable(void);
extern void ReceiveData_Runnable(void);
extern void DisplayTimeMode_Runnable(void);
extern void StopWatchMode_Runnable(void);

const runnable_t runnables[NUM_OF_RUNNABLES]=
{
	[FIRST_RUNNABLE]={.name="LCD", .firstDelayMs=2 , .periodicityMs=2, .cb=LCD_Task },
	[SECOND_RUNNABLE]={.name="KeypadGetKey", .firstDelayMs=5 , .periodicityMs=10, .cb=KEYPADGetKey_Runnable},
    [THIRD_RUNNABLE]={.name="SendData", .firstDelayMs=6 , .periodicityMs=60, .cb=SendData_Runnable },
	[FOURTH_RUNNABLE]={.name="ReceiveData", .firstDelayMs=2 , .periodicityMs=30, .cb=ReceiveData_Runnable },
	[FIFTH_RUNNABLE]={.name="Display", .firstDelayMs=0 , .periodicityMs=250, .cb=DisplayTimeMode_Runnable },
	[SIXTH_RUNNABLE]={.name="StopWatch", .firstDelayMs=400 , .periodicityMs=400, .cb=StopWatchMode_Runnable },
};

