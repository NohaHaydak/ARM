/*
 * sched_main.c
 *
 *  Created on: Mar 26, 2024
 *      Author: Noha
 */
#include "../../SERVICE/INCLUDES/sched_cfg.h"
#include "../../MCAL/INCLUDES/RCC.h"
#include "../../HAL/INCLUDES/LED.h"
void main(void)
{
	u16 AHBprescalerValue=2;
	u8 APBprescalerValue=2;
	RCC_ConfigurePrescaler(peripheral_GPIOA ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOA,peri_status_enabled);
	LED_init();
	sched_init();
}



