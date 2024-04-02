/*
 * sched_cfg.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#include "../INCLUDES/sched_cfg.h"
/*extern void ToggleGreenLed(void);
extern void ToggleYellowLed(void);
extern void ToggleRedLed(void);
extern void trafficLight_runnable(void);*/
extern void LCD_task(void);
void Write_task(void);
const runnable_t runnables[NUM_OF_RUNNABLES]=
{
	[FIRST_RUNNABLE]={.name="LCD", .firstDelayMs=0 , .periodicityMs=1, .cb=LCD_task }/*,
	[SECOND_RUNNABLE]={.name="greenLed", .firstDelayMs=0 , .periodicityMs=2000, .cb=Write_task},
    [THIRD_RUNNABLE]={.name="yellowLed", .firstDelayMs=0 , .periodicityMs=300, .cb=ToggleGreenLed }*/
};

void Write_task(void)
{
	LCD_WriteString_Asynch("noha");
}
