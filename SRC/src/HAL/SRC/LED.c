/*
 * LED.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Noha
 */

#include "../INCLUDES/LED.h"
extern const LED_cfg_t leds[NUM_OF_LEDS];
u8 LED_init(void)
{
	u8 errorStatus=0;
	GPIO_pin_t led;
	led.pinMode=PIN_STATUS_GP_OUTPUT_PP_PU;
	led.pinSpeed=PIN_SPEED_HIGH_SPEED;
	for(u32 itr=0; itr<NUM_OF_LEDS; itr++)
	{
		led.GPIONum=leds[itr].port;
		led.pinNum=leds[itr].pin;
		GPIO_initPin(led);
	}
	return errorStatus;
}

u8 LED_setState(u32 Copy_led, u8 Copy_state )
{
	u8 errorStatus=0;
	Copy_state^=(leds[Copy_led].connection);
	GPIO_setPinValue(leds[Copy_led].port,leds[Copy_led].pin,Copy_state);
	return errorStatus;
}
u8 LED_toggleLed(u32 Copy_led)
{
	u8 errorStatus=0;
	u8 Loc_ledState=0;
	GPIO_getPinValue(leds[Copy_led].port,leds[Copy_led].pin,&Loc_ledState);
	Loc_ledState^=1;
	return errorStatus;
}



