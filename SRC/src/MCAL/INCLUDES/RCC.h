/*
 * RCC.h
 *
 *  Created on: Feb 15, 2024
 *      Author: Noha
 */

#ifndef MCAL_INCLUDES_RCC_H_
#define MCAL_INCLUDES_RCC_H_

#include <stdio.h>
#include "../../LIB/std_types.h"

#define Num_of_PLLM_bits 6
#define Num_of_PLLN_bits 9
/*PLL CONFIG ERROR STATUS*/
#define PLL_IS_SELECTED_AS_SYSCLK_PLEASE_SWITCH_BEFORE_CONFIG 0
#define PLLN_IS_OUT_OF_RANGE                                  1
#define PLLM_IS_OUT_OF_RANGE                                  2


#define AHB_PRESCALER_VALUE_1   0x00
#define AHB_PRESCALER_VALUE_2   0x80
#define AHB_PRESCALER_VALUE_4   0x90
#define AHB_PRESCALER_VALUE_8   0xA0
#define AHB_PRESCALER_VALUE_16  0xB0
#define AHB_PRESCALER_VALUE_64  0xC0
#define AHB_PRESCALER_VALUE_128 0xD0
#define AHB_PRESCALER_VALUE_256 0xE0
#define AHB_PRESCALER_VALUE_512 0xF0

#define APB_PRESCALER_VALUE_1   0x00
#define APB_PRESCALER_VALUE_2   0x80
#define APB_PRESCALER_VALUE_4   0xA0
#define APB_PRESCALER_VALUE_8   0xC0
#define APB_PRESCALER_VALUE_16  0xE0


#define     PLLP_FACTOR2 0b00
#define		PLLP_FACTOR4 0b01
#define		PLLP_FACTOR6 0b10
#define		PLLP_FACTOR8 0b11

#define clk_Source_HSE 0x00400000
#define clk_Source_HSI 0x00000000
typedef enum
{
	clk_HSE,
	clk_HSEBYP,
	clk_HSI,
	clk_PLL
}RCC_clk_t;

typedef enum
{
	clk_Status_ON,
	clk_Status_OFF
}RCC_clk_Status_t;


typedef enum
{
	/*AHB2*/
	peripheral_USB_OTG_FS,
	/*AHB1*/
	peripheral_DMA2,
	peripheral_DMA1,
	peripheral_CRC,
	peripheral_GPIOH,
	peripheral_GPIOE,
	peripheral_GPIOD,
	peripheral_GPIOC,
	peripheral_GPIOB,
	peripheral_GPIOA,
	/*APB2 BUS LOW SPEED WITH MAX FREQ=42 MHZ*/
	peripheral_TIM11,
	peripheral_TIM10,
	peripheral_TIM9,
	peripheral_EXTI,
	peripheral_SYSCFG,
	peripheral_SPI4_I2S4,
	peripheral_SPI1,
	peripheral_SDIO,
	peripheral_ADC1,
	peripheral_USART6,
	peripheral_USART1,
	peripheral_TIM8,
	peripheral_TIM1,
	/*APB1 BUS LOW SPEED WITH MAX FREQ=42 MHZ*/
	peripheral_PWR,
	peripheral_I2C3,
	peripheral_I2C2,
	peripheral_I2C1,
	peripheral_USART2,
	peripheral_I2S3ext,
	peripheral_SPI3_I2S3,
	peripheral__SPI3_I2S2,
	peripheral_I2S2ext,
	peripheral_IWDG,
	peripheral_WWDG,
	peripheral_RTC_BKP_Registers,
	peripheral_TIM5,
	peripheral_TIM4,
	peripheral_TIM3,
	peripheral_TIM2

}RCC_peripheral_t;

typedef enum
{
	peri_status_enabled,
	peri_status_disabled
}RCC_peripheral_status_t;


u8 RCC_ControlClk(RCC_clk_t MCopy_clk ,RCC_clk_Status_t MCopy_clk_Status);
u8 RCC_ConfigureSysclk(RCC_clk_t MCopyclk);

/**
 *@brief : Function to configure the pll clk .
 *@param : clk source : clk_Source_HSE or clk_Source_HSI
 *@param :PLLM is number between 2,63
 *@param :PLLN is number bet 192, 432
 *@param PLLP: PLLP_factor2,PLLP_FACTOR4,PLLP_FACTOR6,PLLP_FACTOR8
 *@return: Error State.
 */
/*PLL*N/(M*P)*/
u8 RCC_ConfigurePLL(u8 MCopy_clk_Source,u8 MCopy_PLLM_factor,u8 MCopy_PLLP_factor,u16 MCopy_PLLN_factor);
u8 RCC_ControlPeripheral(RCC_peripheral_t MCopy_peripheral ,RCC_peripheral_status_t MCopy_peri_status);

/**
 *@brief : Function to configure prescaler of AHB and APB .
 *@param : MCopy_APB1prescalerValue : APB_PRESCALER_VALUE_1 ,2,4,8 to APB_PRESCALER_VALUE_16
 *@param :MCopy_APB2prescalerValue : APB_PRESCALER_VALUE_1 ,2,4,8 to APB_PRESCALER_VALUE_16
 *@param :MCopy_APB1prescalerValue : AHB_PRESCALER_VALUE_1 ,2,4,8,16,64,128,256 to AHB_PRESCALER_VALUE_512
 *@return: Error State.
 */
u8 RCC_ConfigurePrescaler(u8 MCopy_APB1prescalerValue ,u8 MCopy_APB2prescalerValue ,u16 MCopy_AHBprescalerValue);


#endif /* MCAL_INCLUDES_RCC_H_ */
