/*
 * LED_cfg.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Noha
 */

#include "../../MCAL/INCLUDES/GPIO.h"
#include "../INCLUDES/LED.h"

const LED_cfg_t leds[NUM_OF_LEDS]=
{
	[led_1]={.port= GPIOB, .pin=GPIO_PIN_NUM2, .connection=CONNECTION_FORWARD,.state=VALUE_SET_HIGH},
	[led_2]={.port= GPIOA, .pin=GPIO_PIN_NUM0, .connection=CONNECTION_FORWARD,.state=VALUE_SET_LOW},
	[led_3]={.port= GPIOA, .pin=GPIO_PIN_NUM2, .connection=CONNECTION_FORWARD,.state=VALUE_SET_HIGH}
};

