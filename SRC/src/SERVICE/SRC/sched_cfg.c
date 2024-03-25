/*
 * sched_cfg.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#include "../INCLUDES/sched_cfg.h"
void ToggleGreenLed(void);
void ToggleYellowLed(void);
void ToggleRedLed(void);
const runnable_t runnables[NUM_OF_RUNNABLES]=
{
    [FIRST_RUNNABLE]={.name="greenLed", .firstDelayMs=400 , .periodicityMs=200, .cb=ToggleGreenLed },
    [SECOND_RUNNABLE]={.name="redLed", .firstDelayMs=0 , .periodicityMs=200, .cb=ToggleRedLed },
    [THIRD_RUNNABLE]={.name="yellowLed", .firstDelayMs=200 , .periodicityMs=200, .cb=ToggleYellowLed }
};

void ToggleGreenLed(void)
{

}

void ToggleYellowLed(void)
{

}

void ToggleRedLed(void)
{

}


