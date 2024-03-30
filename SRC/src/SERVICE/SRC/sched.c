/*
 * sched.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#include "../INCLUDES/sched_cfg.h"
#include "../../MCAL/INCLUDES/systick.h"

#define  LOC_TICKMs 1
extern const runnable_t runnables[NUM_OF_RUNNABLES];

static runnableRInfo_t runnableRInfo[NUM_OF_RUNNABLES];
static void sched(void);
static void ticksCb(void);
static u32 pendingTicks=0;
void ticksCb(void)
{
	pendingTicks++;
}
void sched(void)
{
    u32 itr;
    for (itr = 0; itr < NUM_OF_RUNNABLES; itr++)
    {

        if (runnables[itr].cb && runnableRInfo[itr].reamainingTime==0)
        {
            runnables[itr].cb();
            runnableRInfo[itr].reamainingTime=runnables[itr].periodicityMs;
        }
        runnableRInfo[itr].reamainingTime-=LOC_TICKMs;
    }

}
void sched_start(void)
{
    MSTK_start();
    while (1)
    {
    	pendingTicks--;
    	sched();
    }

}
void sched_init(void)
{
    u32 itr;
    for (itr = 0; itr < NUM_OF_RUNNABLES; itr++)
    {
        runnableRInfo[itr].runnable=runnables[itr];
        if (runnables[itr].cb && runnableRInfo[itr].reamainingTime==0)
        {
            runnableRInfo[itr].reamainingTime=runnables[itr].firstDelayMs;
        }
    }

    MSTK_init(STK_MODE_PERIODIC);
    MSTK_setTime_ms(1);
    MSTK_SetCallBack(ticksCb);
    sched_start();
}
