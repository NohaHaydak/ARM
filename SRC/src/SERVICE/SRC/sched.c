/*
 * sched.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#include "sched.h"
#include "sched_cfg.h"
#include "systick.h"


extern const runnable_t runnables[NUM_OF_RUNNABLES];

extern u32 G_STK_freq;
static runnableRInfo_t runnableRInfo[NUM_OF_RUNNABLES];
static void sched(void);
void sched_init(void)
{
    u32 itr;
    for (itr = 0; itr < NUM_OF_RUNNABLES; itr++)
    {
        runnableRInfo[itr].runnable=runnables[itr];
        if (runnables[itr].cb && runnableRInfo[itr].reamainingTime==0)
        {
            runnableRInfo[itr].reamainingTime=runnables[itr].periodicityMs+runnables[itr].firstDelayMs;
        }
    }
    MSTK_init(STK_MODE_PERIODIC);
    MSTK_setTime_ms(1);
    MSTK_SetCallBack(sched);
    sched_start();
}

void sched_start(void)
{
    MSTK_start();
    while (1);
    {

    }

}

void sched(void)
{
    u32 itr;
    u32 loc_ticMs=1000/STK_CLKFREQ;

    for (itr = 0; itr < NUM_OF_RUNNABLES; itr++)
    {
        runnableRInfo[itr].reamainingTime-=G_STK_freq;
        if (runnables[itr].cb && runnableRInfo[itr].reamainingTime==0)
        {
            runnables[itr].cb();
        }
    }

}



