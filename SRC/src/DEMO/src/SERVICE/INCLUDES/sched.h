/*
 * sched.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Noha
 */
#ifndef SERVICE_INCLUDES_SCHED_H_
#define SERVICE_INCLUDES_SCHED_H_
#include"stdio.h"
#include"../../LIB/std_types.h"
typedef void(* runnableCb_t) (void);
typedef struct
{
    char* name;
    u32 periodicityMs;
    runnableCb_t cb;
    u32 firstDelayMs;
}runnable_t;

void sched_init(void);
void sched_start(void);
#endif /* SERVICE_INCLUDES_SCHED_H_ */
