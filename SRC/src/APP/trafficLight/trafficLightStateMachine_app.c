/*
 * trafficLightStateMachine_app.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Noha
 */

#include "../../SERVICE/INCLUDES/sched_cfg.h"
#include "../../MCAL/INCLUDES/RCC.h"
#include "../../HAL/INCLUDES/LED.h"
#include "../../HAL/INCLUDES/SWITCH.h"

#define GLed 0
#define RLed 1
#define YLed 2
#define PERIODICITY 2


void trafficLight_runnable(void);

//runnable each 2 sec
void trafficLight_runnable(void)
{
	static u8 state=GLed;
	static u32 Loc_Sec=0;
	static u8 pervious;
	Loc_Sec+=PERIODICITY;
	switch(state)
	{
	case GLed:
		LED_setState(led_3, LED_ON );
		LED_setState(led_2, LED_OFF );
		LED_setState(led_1, LED_OFF );

		if(Loc_Sec==6000)
		{
			state=YLed;
			Loc_Sec=0;
			pervious=GLed;
		}
		else
		{
			//do nothing
		}
		break;
	case RLed:
		LED_setState(led_3, LED_OFF );
		LED_setState(led_2, LED_ON );
		LED_setState(led_1, LED_OFF );

		if(Loc_Sec==2000)
		{
			state=YLed;
			Loc_Sec=0;
			pervious=RLed;
		}
		else
		{
			//do nothing
		}
		break;

	case YLed:
		LED_setState(led_3, LED_OFF );
		LED_setState(led_2, LED_OFF );
		LED_setState(led_1, LED_ON );
		if(Loc_Sec==2000&&pervious==GLed)
		{
			state=RLed;
			Loc_Sec=0;
		}
		else if(Loc_Sec==4000&&pervious==RLed)
		{
			state=GLed;
			Loc_Sec=0;
		}
		else
		{
			//do nothing
		}
		break;

	default:

		break;
	}
}


