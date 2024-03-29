/*
 * sched_app.c
 *
 *  Created on: Mar 26, 2024
 *      Author: Noha
 */

#include "../../HAL/INCLUDES/LED.h"
void ToggleGreenLed(void);
void ToggleYellowLed(void);
void ToggleRedLed(void);

void ToggleGreenLed(void)
{
	LED_setState(led_1, LED_ON );
	LED_setState(led_2, LED_OFF );
	LED_setState(led_3, LED_OFF );
}

void ToggleYellowLed(void)
{

	LED_setState(led_2, LED_ON );
	LED_setState(led_1, LED_OFF );
	LED_setState(led_3, LED_OFF );
}

void ToggleRedLed(void)
{
	LED_setState(led_3, LED_ON );
	LED_setState(led_2, LED_OFF );
	LED_setState(led_1, LED_OFF );
}

