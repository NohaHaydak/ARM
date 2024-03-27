/*
 * systick_main.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Noha
 */
#include"../MCAL/INCLUDES/Systick.h"
#include "../MCAL/INCLUDES/RCC.h"
#include "../HAL/INCLUDES/LED.h"

void LedOn (void);
void main(void)
{
	u16 AHBprescalerValue=2;
	u8 APBprescalerValue=2;
	RCC_ConfigurePrescaler(peripheral_GPIOA ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOA,peri_status_enabled);
	LED_init();
	MSTK_init(STK_MODE_PERIODIC);
	MSTK_start();
	MSTK_setTime_ms(200);
	MSTK_SetCallBack(LedOn);
	APBprescalerValue=2;
	while(1)
	{

	}

}

void LedOn (void)
{
	LED_setState(led_2, LED_ON );
}
