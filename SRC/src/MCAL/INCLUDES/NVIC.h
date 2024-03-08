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

#define EXCEDED_ALLAOWED_INTRNUM 0
#define STATUS_OK 1
#define WRONG_PRIORITY_CFG 2

#define FOUR_BIT_GROUP_NO_SUBGROUB   0x05FA0300
#define THREE_BIT_GROUP_ONE_SUBGROUB 0x05FA0400
#define TWO_BIT_GROUP_TWO_SUBGROUB   0x05FA0500
#define ONE_BIT_GROUP_THREE_SUBGROUB 0x05FA0600
//close nesting
#define NO_BIT_GROUP_FOUR_SUBGROUB   0x05FA0700

/*PRIORITY IP*/
#define NO_GROUP 100
#define NO_SUBGROUP 100


u8 NVIC_EnablePriINTR(u8 MCopy_interruptiID);
u8 NVIC_DisablePriINTR(u8 MCopy_interruptiID);
u8 NVIC_SetPendingForSw_INTR(u8 MCopy_interruptiID);
u8 NVIC_ClrPending(u8 MCopy_interruptiID);
u8 NVIC_GetActiveStatus(u8 MCopy_interruptiID, u8*MCopy_Status);
u8 NVIC_SetPriority(u8 MCopy_PriorityConfiguration,u8 MCopy_interruptiID ,u8 MCopy_GroupPriorityNum , u8 MCopy_subgroupNum);
u8 NVIC_TriggerTntrBySoftware(u8 MCopy_interruptiID);




#endif /* MCAL_INCLUDES_NVIC_H_ */
