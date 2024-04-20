/*
 * HRCC_cfg.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Nada
 */

#ifndef HAL_HRCC_CFG_H_
#define HAL_HRCC_CFG_H_

#include "STD_TYPES.h"

/* Error Possibilities */

#define Ok			    0
#define NotOk		    1
#define NullPointer     2
#define WrongChoice     3

/* Periphrals to be enabled or disabled */

typedef enum
{
    /*Periphrals on AHB1 bus*/
    GPIOAEN,
	GPIOBEN,
	GPIOCEN,
	GPIODEN,
	GPIOEEN,
	GPIOHEN,
	CRCEN,
	DMA1EN,
	DMA2EN,
    /*Periphrals on AHB2 bus*/
    OTGFSEN,
    /*Periphrals on APB1 bus*/
    TIM2EN,
	TIM3EN,
	TIM4EN,
	TIM5EN,
	WWDGEN,
	SPI2EN,
	SPI3EN,
	USART2EN,
	I2C1EN,
	I2C2EN,
	I2C3EN,
	PWREN,
    /*Periphrals on APB2 bus*/
    TIM1EN,
	USART1EN,
	USART6EN,
	ADC1EN,
	SDIOEN,
	SPI1EN,
	SPI4EN,
	SYSCFGEN,
	TIM9EN,
	TIM10EN,
	TIM11EN
}HRCC_Periphrals_t;

/* APIs */

u8 HRCC_EnablePeriphral (u8 Periphral_Name);
u8 HRCC_DisablePeriphral (u8 Periphral_Name);

#endif /* HAL_HRCC_CFG_H_ */