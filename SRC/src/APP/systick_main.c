/*
 * Systick_msin.c
 *
 *  Created on: Mar 31, 2024
 *      Author: Noha
 */

#include"../MCAL/INCLUDES/Systick.h"
#include "../MCAL/INCLUDES/RCC.h"
#include "../HAL/INCLUDES/LED.h"

void LEDToggle (void);
void main(void)
{
	u16 AHBprescalerValue=2;
	u8 APBprescalerValue=2;
	RCC_ConfigurePrescaler(peripheral_GPIOA ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOA ,peri_status_enabled);
	LED_init();
	MSTK_init(STK_MODE_PERIODIC);
	MSTK_setTime_ms(2000);
	MSTK_SetCallBack(LEDToggle);
	MSTK_start();
	APBprescalerValue=2;
	while(1)
	{

	}

}

void LEDToggle (void)
{
	LED_toggleLed(led_3);
}


