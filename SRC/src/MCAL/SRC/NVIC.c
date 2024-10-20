/*
 * NVIC.c
 *
 *  Created on: Mar 8, 2024
 *      Author: Noha
 */
#include"../INCLUDES/NVIC.h"


#define INTR_NUMS 240
#define SCB_AIRCR_CLR_MASK 0x05FA0000
#define OFFESET_FOUR 4
typedef struct
{
    u32 NVIC_ISER[32];
    u32 NVIC_ICER[32];
    u32 NVIC_ISPR[32];
    u32 NVIC_ICPR[32];
    u32 NVIC_IABR[64];
    u8  NVIC_IPR[240];
    u32 Reserved[644];
    u32 NVIC_STIR;
}NVIC_t;


typedef struct
{
    u32 SCB_CPUID;
    u32 SCB_ICSR;
    u32 SCB_VTOR;
    u32 SCB_AIRCR;
    u32 SCB_SCR;
    u32 SCB_CCR;
    u32 SCB_SHPR1;
    u32 SCB_SHPR2;
    u32 SCB_SHPR3;
    u32 SCB_SHCSR;
    u32 SCB_CFSR;
    u32 SCB_MMSR;
    u32 SCB_BFSR;
    u32 SCB_UFSR;
    u32 SCB_HFSR;
    u32 SCB_MMAR;
    u32 SCB_BFAR;
    u32 SCB_AFSR;
}SCB_t;


static NVIC_t volatile *const NVIC =((NVIC_t volatile *const )0xE000E100);
static SCB_t volatile *const SCB =((SCB_t volatile *const )0xE000ED00);

u8 NVIC_EnablePriINTR(u8 MCopy_interruptiID)
{
    u8 local_BitNum=MCopy_interruptiID%32;
    u8 local_RegNum=MCopy_interruptiID/32;
    u8 Local_errorStatus;

    if(MCopy_interruptiID>INTR_NUMS)
    {
        Local_errorStatus=EXCEDED_ALLAOWED_INTRNUM;
    }
    else
    {
        //clr pending at first
        //NVIC->NVIC_ICPR[local_RegNum]=(1<<local_BitNum);
        //enable intr
        NVIC->NVIC_ISER[local_RegNum]=(1<<local_BitNum);
        Local_errorStatus= STATUS_OK;
    }
    return  Local_errorStatus;

}
u8 NVIC_DisablePriINTR(u8 MCopy_interruptiID)
{
    u8 local_BitNum=MCopy_interruptiID%32;
    u8 local_RegNum=MCopy_interruptiID/32;
    u8 Local_errorStatus;
    if(MCopy_interruptiID>INTR_NUMS)
    {
        Local_errorStatus=EXCEDED_ALLAOWED_INTRNUM;
    }
    else
    {
        //disable intr
        NVIC->NVIC_ICER[local_RegNum]=(1<<local_BitNum);
        Local_errorStatus= STATUS_OK;
    }
    return  Local_errorStatus;
}
u8 NVIC_SetPendingForSw_INTR(u8 MCopy_interruptiID)
{
    u8 local_BitNum=MCopy_interruptiID%32;
    u8 local_RegNum=MCopy_interruptiID/32;
    u8 Local_errorStatus;
    u8 Local_InterruptState=NVIC->NVIC_ISER[local_RegNum];

    if(MCopy_interruptiID>INTR_NUMS)
    {
        Local_errorStatus=EXCEDED_ALLAOWED_INTRNUM;
    }
    else if(Local_InterruptState==1)
    {
    	Local_errorStatus=NOT_ALLOWED;
    }
    else
    {
        //set pending
        NVIC->NVIC_ISPR[local_RegNum]=(1<<local_BitNum);
        Local_errorStatus= STATUS_OK;
    }
    return  Local_errorStatus;

}
u8 NVIC_ClrPending(u8 MCopy_interruptiID)
{
    u8 local_BitNum=MCopy_interruptiID%32;
    u8 local_RegNum=MCopy_interruptiID/32;
    u8 Local_errorStatus;
    if(MCopy_interruptiID>INTR_NUMS)
    {
        Local_errorStatus=EXCEDED_ALLAOWED_INTRNUM;
    }
    else
    {
        //clr pending
        NVIC->NVIC_ICPR[local_RegNum]=(1<<local_BitNum);
        Local_errorStatus= STATUS_OK;
    }
    return  Local_errorStatus;
}
u8 NVIC_GetActiveStatus(u8 MCopy_interruptiID, u8*MCopy_Status)
{
    u8 local_BitNum=MCopy_interruptiID%32;
    u8 local_RegNum=MCopy_interruptiID/32;
    u8 Local_errorStatus;

    if(MCopy_interruptiID>INTR_NUMS)
    {
        Local_errorStatus=EXCEDED_ALLAOWED_INTRNUM;
    }
    else
    {
        //get satus
        *MCopy_Status=(NVIC->NVIC_ICPR[local_RegNum]>>local_BitNum)&1;
        Local_errorStatus= STATUS_OK;
    }
    return  Local_errorStatus;

}
/*priorities from 0 to 15 as it's 16 level of nesting and is represented by group/premption num*/
u8 NVIC_SetPriority(u8 MCopy_interruptiID ,u8 MCopy_GroupPriorityNum , u8 MCopy_subgroupNum)
{
    u8 Local_errorStatus;
    u8 Local_GroupPriority;
    u8 Local_subgroupNum;
    u8 Local_Priority;
	#if PRIORITY_CONFIGURATION==FOUR_BIT_GROUP_NO_SUBGROUB
    u32 Local_PriorityConfiguration= (FOUR_BIT_GROUP_NO_SUBGROUB-0x05FA0300)>>8;
	#elif PRIORITY_CONFIGURATION==THREE_BIT_GROUP_ONE_SUBGROUB
    u32 Local_PriorityConfiguration= (THREE_BIT_GROUP_ONE_SUBGROUB-0x05FA0300)>>8;
	#elif PRIORITY_CONFIGURATION==TWO_BIT_GROUP_TWO_SUBGROUB
    u32 Local_PriorityConfiguration= (TWO_BIT_GROUP_TWO_SUBGROUB-0x05FA0300)>>8;
	#elif PRIORITY_CONFIGURATION==ONE_BIT_GROUP_THREE_SUBGROUB
    u32 Local_PriorityConfiguration= (ONE_BIT_GROUP_THREE_SUBGROUB-0x05FA0300)>>8;
	#elif PRIORITY_CONFIGURATION==NO_BIT_GROUP_FOUR_SUBGROUB
    u32 Local_PriorityConfiguration= (NO_BIT_GROUP_FOUR_SUBGROUB-0x05FA0300)>>8;
	#endif


	#if PRIORITY_CONFIGURATION==FOUR_BIT_GROUP_NO_SUBGROUB
    SCB->SCB_AIRCR=FOUR_BIT_GROUP_NO_SUBGROUB;
	#elif PRIORITY_CONFIGURATION==THREE_BIT_GROUP_ONE_SUBGROUB
    SCB->SCB_AIRCR=THREE_BIT_GROUP_ONE_SUBGROUB;
	#elif PRIORITY_CONFIGURATION==TWO_BIT_GROUP_TWO_SUBGROUB
    SCB->SCB_AIRCR=TWO_BIT_GROUP_TWO_SUBGROUB;
	#elif PRIORITY_CONFIGURATION==ONE_BIT_GROUP_THREE_SUBGROUB
    SCB->SCB_AIRCR=ONE_BIT_GROUP_THREE_SUBGROUB;
	#elif PRIORITY_CONFIGURATION==NO_BIT_GROUP_FOUR_SUBGROUB
    SCB->SCB_AIRCR=NO_BIT_GROUP_FOUR_SUBGROUB;
	#endif


    if(Local_Priority>PRIORITY_NUM_15 && Local_PriorityConfiguration>4)
    {
            Local_errorStatus= WRONG_PRIORITY_CFG;
    }
    else
    {
    	    if(MCopy_subgroupNum==NO_SUBGROUP)
    	    {
    	    	Local_GroupPriority=(MCopy_GroupPriorityNum<<OFFESET_FOUR);
    	    	Local_Priority=Local_GroupPriority;
    	    }
    	    else if(MCopy_GroupPriorityNum==NO_GROUP)
    	    {
    	    	Local_Priority=MCopy_subgroupNum<<OFFESET_FOUR;
    	    }
    	    else
    	    {
    	    	Local_GroupPriority=(MCopy_GroupPriorityNum<<OFFESET_FOUR)<<Local_PriorityConfiguration;
    	    	Local_subgroupNum=MCopy_subgroupNum<<OFFESET_FOUR;
    	    	Local_Priority=Local_GroupPriority|Local_subgroupNum;
    	    }
    	    //clr IPR first
    	    //NVIC->NVIC_IPR[MCopy_interruptiID]&=0x0;
    	    NVIC->NVIC_IPR[MCopy_interruptiID]=Local_Priority;
    }

    return Local_errorStatus;
}

u8 NVIC_TriggerTntrBySoftware(u8 MCopy_interruptiID)
{
    u8 Local_errorStatus;

    if(MCopy_interruptiID>INTR_NUMS)
    {
        Local_errorStatus=EXCEDED_ALLAOWED_INTRNUM;
    }
    else
    {
        //trigger specific peri interrupt using s.w
        NVIC->NVIC_STIR|=(1<<MCopy_interruptiID);

        Local_errorStatus= STATUS_OK;
    }
    return  Local_errorStatus;
}



