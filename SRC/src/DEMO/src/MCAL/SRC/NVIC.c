/*
 * NVIC.c
 *
 *  Created on: Mar 5, 2024
 *      Author: Nada
 */

#include "NVIC.h"

/* Registers Base Address */
#define NVIC_BASEADD            0xE000E100
#define SCB_BASEADD             0xE000ED00

/* Number of IRQs per register */
#define IRQS_PER_REG            32
#define IRQs_PER_PRI_REG        4

/* Number (can be used as index of bits)*/
#define ZERO                    0
#define ONE                     1
#define FOUR                    4
#define FIVE                    5
#define SEVEN                   7
#define EIGHT                   8

/* Shifting numbers*/
#define SHIFT_EIGHT             8

/* Name of bit in a register */
#define BIT_FOUR                4

/*Masks to get bits*/
#define MASK_ONE_BIT		0x00000001
#define MASK_THREE_BITS     0x00000007
#define MASK_FOUR_BITS      0x0000000F

/* NVIC Regesters */
typedef struct
{
    volatile u32 NVIC_ISER[8];
    volatile u32 Reserved1[24];
    volatile u32 NVIC_ICER[8];
    volatile u32 Reserved2[24];
    volatile u32 NVIC_ISPR[8];
    volatile u32 Reserved3[24];
    volatile u32 NVIC_ICPR[8];
    volatile u32 Reserved4[24];
    volatile u32 NVIC_IABR[8];
    volatile u32 Reserved5[56];
    volatile u32 NVIC_IPR[60];
    volatile u32 Reserved6[580];
    volatile u32 NVIC_STIR;
}NVIC_Regs_t;

typedef struct
{
    volatile u32 SCB_CPUID;
    volatile u32 SCB_ICSR;
    volatile u32 SCB_VTOR;
    volatile u32 SCB_AIRCR;
    volatile u32 SCB_SCR;
    volatile u32 SCB_CCR;
    volatile u32 SCB_SHPR1;
    volatile u32 SCB_SHPR2;
    volatile u32 SCB_SHPR3;
    volatile u32 SCB_SHCSR;
    volatile u32 SCB_CFSR;
    volatile u32 SCB_HFSR;
    volatile u32 SCB_reserved;
    volatile u32 SCB_MMAR;
    volatile u32 SCB_BFAR;
    volatile u32 SCB_AFSR;
}SCB_Regs_t;

NVIC_Regs_t *NVIC_Regs = (NVIC_Regs_t*)NVIC_BASEADD;
SCB_Regs_t *SCB_Regs = (SCB_Regs_t*)SCB_BASEADD;

/* APIs Implementations */

u8 NVIC_EnableIRQ(IRQ_index_t IRQ)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else
    {
        u8 IRQ_bit = IRQ % IRQS_PER_REG;
        u8 IRQ_reg = IRQ / IRQS_PER_REG;
        NVIC_Regs->NVIC_ISER[IRQ_reg] = (ONE << IRQ_bit);
    }

    return ErrorStatus;
}

u8 NVIC_DisableIRQ(IRQ_index_t IRQ)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else
    {
        u8 IRQ_bit = IRQ % IRQS_PER_REG;
        u8 IRQ_reg = IRQ / IRQS_PER_REG;
        NVIC_Regs->NVIC_ICER[IRQ_reg] = (ONE << IRQ_bit);
    }

    return ErrorStatus;
}

u8 NVIC_GetPendingIRQ(IRQ_index_t IRQ, u8 *PendingStatus)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else if (PendingStatus==NULL)
    {
        ErrorStatus = NullPointer;
    }

    else
    {
        u8 IRQ_bit = IRQ % IRQS_PER_REG;
        u8 IRQ_reg = IRQ / IRQS_PER_REG;
        *PendingStatus = ((NVIC_Regs->NVIC_ISPR[IRQ_reg]) >> IRQ_bit) & MASK_ONE_BIT;
    }

    return ErrorStatus;
}
u8 NVIC_SetPendingIRQ(IRQ_index_t IRQ)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else
    {
        u8 IRQ_bit = IRQ % IRQS_PER_REG;
        u8 IRQ_reg = IRQ / IRQS_PER_REG;
        NVIC_Regs->NVIC_ISPR[IRQ_reg] = (ONE << IRQ_bit);
    }

    return ErrorStatus;
}

u8 NVIC_ClearPendingIRQ(IRQ_index_t IRQ)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else
    {
        u8 IRQ_bit = IRQ % IRQS_PER_REG;
        u8 IRQ_reg = IRQ / IRQS_PER_REG;
        NVIC_Regs->NVIC_ICPR[IRQ_reg] = (ONE << IRQ_bit);
    }

    return ErrorStatus;
}
u8 NVIC_GetActive(IRQ_index_t IRQ, u8 *ActiveStatus)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else if (ActiveStatus==NULL)
    {
        ErrorStatus = NullPointer;
    }

    else
    {
        u8 IRQ_bit = IRQ % IRQS_PER_REG;
        u8 IRQ_reg = IRQ / IRQS_PER_REG;
        *ActiveStatus = ((NVIC_Regs->NVIC_IABR[IRQ_reg]) >> IRQ_bit) & MASK_ONE_BIT;
    }

    return ErrorStatus;
}

static u8 Two_Power(u8 power)
{
    u8 res = 1;
    for (u8 iterator = 0; iterator < power; iterator++)
    {
        res *= 2;
    }
    return res;
}

u8 NVIC_SetPriority(IRQ_index_t IRQ, u32 PRIGROUP, u8 PreemptionPri, u8 SubGroupPri)
{
    u8 ErrorStatus = Ok;
   
    u8 Local_SubGroupBits = 0;
    u8 Local_PreemptionBits = 0;
    u8 Local_MinSubGroupPri = 0;
    u8 Local_MaxSubGroupPri = 0;
    u8 Local_MinPreemptionPri = 0;
    u8 Local_MaxPreemptionPri = 0;
    u8 Priority = 0; 

    if (IRQ >= IRQs_Number || IRQ < ZERO || PRIGROUP<PRIGROUP0 || PRIGROUP>PRIGROUP7)
    {
        ErrorStatus = WrongChoice;
    }
    else
    {
        Local_SubGroupBits = ((PRIGROUP>>SHIFT_EIGHT)&MASK_THREE_BITS)+ONE;
        Local_PreemptionBits = EIGHT - Local_SubGroupBits;

        if (Local_SubGroupBits==ONE)
        {
            Local_MinPreemptionPri = ZERO;
            Local_MaxPreemptionPri = Two_Power(BIT_FOUR)-ONE;
        }
        
        else if (Local_SubGroupBits==EIGHT)
        {
            Local_MinSubGroupPri = ZERO;
            Local_MaxSubGroupPri = Two_Power(BIT_FOUR)-ONE;
        }

        else if (Local_SubGroupBits > FOUR && Local_SubGroupBits < EIGHT)
        {
            Local_MinSubGroupPri = ZERO;
            Local_MaxSubGroupPri = Two_Power(Local_SubGroupBits-FOUR)-ONE;
            Local_MinPreemptionPri = ZERO;
            Local_MaxPreemptionPri = Two_Power(Local_PreemptionBits)-ONE;
        }
    }
    
    if (PreemptionPri < Local_MinPreemptionPri || PreemptionPri > Local_MaxPreemptionPri || SubGroupPri < Local_MinSubGroupPri || SubGroupPri > Local_MaxSubGroupPri)
    {
        ErrorStatus = NotOk;
    }
    
    else
    {
        switch (Local_SubGroupBits)
        {
        case ONE:
            Priority = PreemptionPri << FOUR;
            break;
        case FIVE...SEVEN:
            Priority = (SubGroupPri << FOUR) | (PreemptionPri << Local_SubGroupBits);
            break;
        case EIGHT:
            Priority = SubGroupPri << FOUR;
            break;
        default:
            ErrorStatus = WrongChoice;
            break;
        }
    }

    if (ErrorStatus == Ok)
    {
        u8 IRQ_bit = IRQ % IRQs_PER_PRI_REG;
        u8 IRQ_reg = IRQ / IRQs_PER_PRI_REG;
        u32 Copy_Reg = NVIC_Regs->NVIC_IPR[IRQ_reg];
        Copy_Reg &= ~(MASK_FOUR_BITS << ((IRQ_bit*EIGHT)+FOUR));
        Copy_Reg |= (Priority << IRQ_bit*EIGHT);
        NVIC_Regs->NVIC_IPR[IRQ_reg] = Copy_Reg;
        SCB_Regs->SCB_AIRCR = PRIGROUP;
    }

    return ErrorStatus;
}
u8 NVIC_GetPriority(IRQ_index_t IRQ, u8 *Priority)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else if (Priority==NULL)
    {
        ErrorStatus = NullPointer;
    }

    else
    {
        u8 IRQ_bit = IRQ % IRQs_PER_PRI_REG;
        u8 IRQ_reg = IRQ / IRQs_PER_PRI_REG;
        *Priority = ((NVIC_Regs->NVIC_IPR[IRQ_reg]) >> ((IRQ_bit*EIGHT)+FOUR)) & MASK_FOUR_BITS;
    }

    return ErrorStatus;    
}

u8 NVIC_GenerateSWInt(IRQ_index_t IRQ)
{
    u8 ErrorStatus = Ok;

    if (IRQ >= IRQs_Number || IRQ < 0)
    {
        ErrorStatus = WrongChoice;
    }

    else
    {
        NVIC_Regs->NVIC_STIR = IRQ;
    }

    return ErrorStatus;
}