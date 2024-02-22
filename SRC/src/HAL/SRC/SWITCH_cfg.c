/*
 * SWITCH_cfg.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Noha
 */

#include "../../MCAL/INCLUDES/GPIO.h"
#include "../INCLUDES/SWITCH.h"

const SWITCH_cfg_t switches[NUM_OF_SWITCHES]=
{
	[SWITCH_1]={.port= GPIOB, .pin=GPIO_PIN_NUM0, .connection=CONNECTION_PU},
	[SWITCH_2]={.port= GPIOB, .pin=GPIO_PIN_NUM1, .connection=CONNECTION_PU},
	[SWITCH_3]={.port= GPIOC, .pin=GPIO_PIN_NUM0, .connection=CONNECTION_PU}
};


