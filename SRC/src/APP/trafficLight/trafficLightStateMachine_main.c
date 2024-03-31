/*
 * trafficLightStateMachine_main.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Noha
 */
#include "../../SERVICE/INCLUDES/sched_cfg.h"
#include "../../MCAL/INCLUDES/RCC.h"
#include "../../HAL/INCLUDES/LED.h"
#include "../../HAL/INCLUDES/SWITCH.h"

void main(void)
{
	u16 AHBprescalerValue=2;
	u8 APBprescalerValue=2;
	RCC_ConfigurePrescaler(peripheral_GPIOA ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOA,peri_status_enabled);
	RCC_ConfigurePrescaler(peripheral_GPIOB ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOB,peri_status_enabled);
	LED_init();
	sched_init();
	sched_start();

}


