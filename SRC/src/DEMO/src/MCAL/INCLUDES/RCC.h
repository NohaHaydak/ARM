/*
 * RCC.h
 *
 *  Created on: Feb 7, 2024
 *      Author: Nada
 */

#ifndef MCAL_RCC_H_
#define MCAL_RCC_H_

#include "std_types.h"

/* Clock Options */
typedef enum
{
	Clock_HSI,
	Clock_HSE,
	Clock_PLL
}RCC_Clock_t;

/* Clock status */
typedef enum
{
	NotReady,
	Ready
}RCC_Status_t;

/*Periphrals on AHB1 bus*/
typedef enum
{
	AHB1ENR_GPIOAEN,
	AHB1ENR_GPIOBEN,
	AHB1ENR_GPIOCEN,
	AHB1ENR_GPIODEN,
	AHB1ENR_GPIOEEN,
	AHB1ENR_GPIOHEN,
	AHB1ENR_CRCEN,
	AHB1ENR_DMA1EN,
	AHB1ENR_DMA2EN
}AHB1ENR_Peri_t;

/*Periphrals on AHB2 bus*/
typedef enum
{
	AHB2ENR_OTGFSEN
}AHB2ENR_Peri_t;

/*Periphrals on APB1 bus*/
typedef enum
{
	APB1ENR_TIM2EN,
	APB1ENR_TIM3EN,
	APB1ENR_TIM4EN,
	APB1ENR_TIM5EN,
	APB1ENR_WWDGEN,
	APB1ENR_SPI2EN,
	APB1ENR_SPI3EN,
	APB1ENR_USART2EN,
	APB1ENR_I2C1EN,
	APB1ENR_I2C2EN,
	APB1ENR_I2C3EN,
	APB1ENR_PWREN
}APB1ENR_Peri_t;

/*Periphrals on APB2 bus*/
typedef enum
{
	APB2ENR_TIM1EN,
	APB2ENR_USART1EN,
	APB2ENR_USART6EN,
	APB2ENR_ADC1EN,
	APB2ENR_SDIOEN,
	APB2ENR_SPI1EN,
	APB2ENR_SPI4EN,
	APB2ENR_SYSCFGEN,
	APB2ENR_TIM9EN,
	APB2ENR_TIM10EN,
	APB2ENR_TIM11EN
}APB2ENR_Peri_t;


/* Error Possibilities */
#define Ok			    0
#define NotOk		    1
#define NullPointer		2
#define WrongChoice     3

/* APIs */

/*Choose from the clock options*/
u8 RCC_EnableClk (RCC_Clock_t Clock);

u8 RCC_DisableClk (RCC_Clock_t Clock);

u8 RCC_SelectSysClk (RCC_Clock_t Clock);


/* Expect status NotReady or Ready*/
u8 RCC_CheckClkStatus (RCC_Clock_t Clock, RCC_Status_t *ClockStatus);

u8 RCC_SetPLLSource (RCC_Clock_t Clock);

/*	2	<=	M	<=	63
 * 	192 <=	N	<=	432
 *	P = {	2,	4,	6,	8}
 *	2	<=	Q	<=	15
 * */
u8 RCC_ConfigPLL (u32 M, u32 N, u32 P, u32 Q);

/*Choose from periphrals on AHB1 bus*/
u8 RCC_EnableAHB1Peri(AHB1ENR_Peri_t AHB1_Peri);
u8 RCC_DisableAHB1Peri(AHB1ENR_Peri_t AHB1_Peri);

/*Choose from periphrals on AHB2 bus*/
u8 RCC_EnableAHB2Peri(AHB2ENR_Peri_t AHB2_Peri);
u8 RCC_DisableAHB2Peri(AHB2ENR_Peri_t AHB2_Peri);

/*Choose from periphrals on APB1 bus*/
u8 RCC_EnableAPB1Peri(APB1ENR_Peri_t APB1_Peri);
u8 RCC_DisableAPB1Peri(APB1ENR_Peri_t APB1_Peri);

/*Choose from periphrals on APB2 bus*/
u8 RCC_EnableAPB2Peri(APB2ENR_Peri_t APB2_Peri);
u8 RCC_DisableAPB2Peri(APB2ENR_Peri_t APB2_Peri);

#endif /* MCAL_RCC_H_ */