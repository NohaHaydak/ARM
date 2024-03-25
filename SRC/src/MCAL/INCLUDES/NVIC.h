/*
 * NVIC.h
 *
 *  Created on: Mar 8, 2024
 *      Author: Noha
 */

#ifndef MCAL_INCLUDES_NVIC_H_
#define MCAL_INCLUDES_NVIC_H_

#include"stdio.h"
#include"../../LIB/std_types.h"
#include"STM32F401CC.h"
#include "NVIC_CFG.h"


#define EXCEDED_ALLAOWED_INTRNUM 0
#define STATUS_OK 1
#define WRONG_PRIORITY_CFG 2



/*PRIORITY IP*/
#define NO_GROUP 100
#define NO_SUBGROUP 100


u8 NVIC_EnablePriINTR(u8 MCopy_interruptiID);
u8 NVIC_DisablePriINTR(u8 MCopy_interruptiID);
u8 NVIC_SetPendingForSw_INTR(u8 MCopy_interruptiID);
u8 NVIC_ClrPending(u8 MCopy_interruptiID);
u8 NVIC_GetActiveStatus(u8 MCopy_interruptiID, u8*MCopy_Status);
u8 NVIC_SetPriority(u8 MCopy_interruptiID ,u8 MCopy_GroupPriorityNum , u8 MCopy_subgroupNum);
u8 NVIC_TriggerTntrBySoftware(u8 MCopy_interruptiID);




#endif /* MCAL_INCLUDES_NVIC_H_ */
