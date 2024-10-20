/*
 * LCD_main.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Noha
 */

#include "../SERVICE/INCLUDES/sched_cfg.h"
#include "../MCAL/INCLUDES/RCC.h"
#include "../HAL/INCLUDES/LCD.h"
void main(void)
{
	u16 AHBprescalerValue=2;
	u8 APBprescalerValue=2;
	RCC_ConfigurePrescaler(peripheral_GPIOA ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOA,peri_status_enabled);
	RCC_ConfigurePrescaler(peripheral_GPIOB ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOB,peri_status_enabled);
	LCD_enuGotoDDRAM_XY_Asynch(1,9);
	LCD_WriteString_Asynch("noha");
	LCD_ClrScreen_Asynch();
	LCD_enuWriteNumber_Asynch(-15);
	//LCD_enuGotoDDRAM_XY_Asynch(1,10);
	//LCD_enuWriteNumber_Asynch(5);
	sched_init();

	sched_start();

}


