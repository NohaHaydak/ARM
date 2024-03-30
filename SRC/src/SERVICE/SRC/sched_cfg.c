/*
 * sched_cfg.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#include "../INCLUDES/sched_cfg.h"
extern void ToggleGreenLed(void);
extern void ToggleYellowLed(void);
extern void ToggleRedLed(void);
const runnable_t runnables[NUM_OF_RUNNABLES]=
{
	[FIRST_RUNNABLE]={.name="redLed", .firstDelayMs=0 , .periodicityMs=200, .cb=ToggleRedLed },
	[SECOND_RUNNABLE]={.name="greenLed", .firstDelayMs=400 , .periodicityMs=200, .cb=ToggleGreenLed },
    [THIRD_RUNNABLE]={.name="yellowLed", .firstDelayMs=200 , .periodicityMs=200, .cb=ToggleYellowLed }
};
