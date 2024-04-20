/*
 * sched.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#include "../INCLUDES/sched_cfg.h"
#include "../../MCAL/INCLUDES/systick.h"

#define TICKMs 1
extern const runnable_t runnables[NUM_OF_RUNNABLES];

static runnableRInfo_t runnableRInfo[NUM_OF_RUNNABLES];
static void sched(void);
static void ticksCb(void);
static volatile u32 pendingTicks=0;
void ticksCb(void)
{
	pendingTicks++;
}
void sched(void)
{
    u32 itr;
    for (itr = 0; itr < NUM_OF_RUNNABLES; itr++)
    {

        if (runnableRInfo[itr].runnable->cb&& runnableRInfo[itr].remainingTime==0)
        {
            runnables[itr].cb();
            runnableRInfo[itr].remainingTime=runnableRInfo[itr].runnable->periodicityMs;
        }
        runnableRInfo[itr].remainingTime-=TICKMs;
    }

}
void sched_start(void)
{
    MSTK_start();
    while (1)
    {
    	if(pendingTicks)
    	{
    		pendingTicks--;
    		sched();
    	}


    }

}
void sched_init(void)
{
    u32 itr;
    for (itr = 0; itr < NUM_OF_RUNNABLES; itr++)
    {
        runnableRInfo[itr].runnable=&runnables[itr];
        runnableRInfo[itr].remainingTime=runnableRInfo[itr].runnable->firstDelayMs;

    }

    MSTK_init(STK_MODE_PERIODIC);
    MSTK_setTime_ms(TICKMs);
    MSTK_SetCallBack(ticksCb);
}
