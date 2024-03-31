/*
 * sched_cfg.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */

#ifndef SERVICE_INCLUDES_SCHED_CFG_H_
#define SERVICE_INCLUDES_SCHED_CFG_H_

#include "sched.h"
#define FIRST_RUNNABLE  0
#define SECOND_RUNNABLE 1
#define THIRD_RUNNABLE  2

#define NUM_OF_RUNNABLES 3

typedef struct
{
    runnable_t*runnable;
    u32 remainingTime;
}runnableRInfo_t;



#endif /* SERVICE_INCLUDES_SCHED_CFG_H_ */
