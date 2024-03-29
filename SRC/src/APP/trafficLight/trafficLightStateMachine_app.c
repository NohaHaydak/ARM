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
	Loc_Sec+=PERIODICITY;
	switch(state)
	{
	case GLed:

		if(Loc_Sec==6)
		{
			state=YLed;
			Loc_Sec=0;
		}
		else
		{
			//do nothing
		}
		break;
	case RLed:
		if(Loc_Sec==2)
		{
			state=YLed;
			Loc_Sec=0;
		}
		else
		{
			//do nothing
		}
		break;

	case YLed:
		if(Loc_Sec==2)
		{
			state=RLed;
			Loc_Sec=0;
		}
		else if(Loc_Sec==20)
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


