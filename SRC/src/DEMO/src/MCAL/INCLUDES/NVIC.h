/*
 * NVIC.h
 *
 *  Created on: Mar 5, 2024
 *      Author: Nada
 */

#ifndef MCAL_NVIC_H_
#define MCAL_NVIC_H_

#include "std_types.h"

/* IRQ indecies */
typedef enum
{
    WWDG,
    EXTI16_PVD,
    EXTI21_TAMP_STAMP,
    EXTI22_RTC_WKUP,
    FLASH,
    RCC,
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    DMA1_Stream0,
    DMA1_Stream1,
    DMA1_Stream2,
    DMA1_Stream3,
    DMA1_Stream4,
    DMA1_Stream5,
    DMA1_Stream6,
    ADC,
    EXTI9_5 = 23,
    TIM1_BRK_TIM9,
    TIM1_UP_TIM10,
    TIM1_TRG_COM_TIM11,
    TIM1_CC,
    TIM2,
    TIM3,
    TIM4,
    I2C1_EV,
    I2C1_ER,
    I2C2_EV,
    I2C2_ER,
    SPI1,
    SPI2,
    NVIC_USART1,
    NVIC_USART2,
    EXTI15_10 = 40,
    EXTI17,
    EXTI18,
    DMA1_Stream7 = 47,
    SDIO = 49,
    TIM5,
    SPI3,
    DMA2_Stream0 = 56,
    DMA2_Stream1,
    DMA2_Stream2,
    DMA2_Stream3,
    DMA2_Stream4,
    OTG_FS = 67,
    DMA2_Stream5,
    DMA2_Stream6,
    DMA2_Stream7,
    NVIC_USART6,
    I2C3_EV,
    I2C3_ER,
    FPU = 81,
    SPI4 = 84,
    IRQs_Number
}IRQ_index_t;

/* Priority Groups */
#define PRIGROUP0		0x05FA0000 /* Subgroup bits = {0} */ 
#define PRIGROUP4		0x05FA0400 /* Subgroup bits = [0,4] */
#define PRIGROUP5		0x05FA0500 /* Subgroup bits = [0,5] */
#define PRIGROUP6		0x05FA0600 /* Subgroup bits = [0,6] */
#define PRIGROUP7		0x05FA0700 /* Subgroup bits = [0,7] */

/* Error Possibilities */
#define Ok				0
#define NotOk			1
#define NullPointer		2
#define WrongChoice		3

/* Pending Status */
#define Int_NotPending  0
#define Int_Pending     1

/* APIs */

u8 NVIC_EnableIRQ(IRQ_index_t IRQ);
u8 NVIC_DisableIRQ(IRQ_index_t IRQ);
u8 NVIC_GetPendingIRQ(IRQ_index_t IRQ, u8 *PendingStatus);
u8 NVIC_SetPendingIRQ(IRQ_index_t IRQ);
u8 NVIC_ClearPendingIRQ(IRQ_index_t IRQ);
u8 NVIC_GetActive(IRQ_index_t IRQ, u8 *ActiveStatus);
u8 NVIC_SetPriority(IRQ_index_t IRQ, u32 PRIGROUP, u8 PreemptionPri, u8 SubGroupPri);
u8 NVIC_GetPriority(IRQ_index_t IRQ, u8 *Priority);
u8 NVIC_GenerateSWInt(IRQ_index_t IRQ);


#endif /* MCAL_NVIC_H_ */