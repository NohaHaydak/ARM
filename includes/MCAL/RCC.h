/*
 * RCC.h
 *
 * Created: 2/4/2024 12:21:44 PM
 *  Author: Noha
 */ 


#ifndef RCC_H_
#define RCC_H_


#include <stdio.h>
#include "std_types.h"

#define Num_of_PLLM_bits 6
#define Num_of_PLLN_bits 9
/*PLL CONFIG ERROR STATUS*/
#define PLL_IS_SELECTED_AS_SYSCLK_PLEASE_SWITCH_BEFORE_CONFIG 0
#define PLLN_IS_OUT_OF_RANGE                                  1
#define PLLM_IS_OUT_OF_RANGE                                  2

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
	clk_Source_HSE,
	clk_Source_HSI
}RCC_PLL_ClkSource_t;

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
/*PLL*N/(M*P)*/
u8 RCC_ConfigurePLL(RCC_PLL_ClkSource_t MCopy_clk_Source,u8 MCopy_PLLM_factor,u8 MCopy_PLLP_factor,u8 MCopy_PLLN_factor);
u8 RCC_ControlPeripheral(RCC_peripheral_t MCopy_peripheral ,RCC_peripheral_status_t MCopy_peri_status);
u8 RCC_ConfigurePrescaler(RCC_peripheral_t MCopy_peripheral ,u16 MCopy_AHBprescalerValue ,u8 MCopy_APBprescalerValue);


#endif /* RCC_H_ */