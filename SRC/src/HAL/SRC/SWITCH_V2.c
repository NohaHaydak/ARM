/*
 * SWITCH_V2.c
 *
 *  Created on: Mar 26, 2024
 *      Author: Noha
 */
#include "../../MCAL/INCLUDES/GPIO.h"
#include "../INCLUDES/SWITCH.h"

extern const SWITCH_cfg_t switches[NUM_OF_SWITCHES];
u8 G_swState[NUM_OF_SWITCHES];

u8 SWITCH_runnable(void);

u8 SWITCH_init(void)
{
	u8 errorStatus=0;
	GPIO_pin_t sw;
	sw.pinSpeed=PIN_SPEED_HIGH_SPEED;
	for(u32 itr=0; itr<NUM_OF_SWITCHES; itr++)
	{
		switch(switches[itr].connection)
		{
			case CONNECTION_PU:
				sw.pinMode=PIN_STATUS_INPUT_PU;
				break;
			case CONNECTION_PD:
				sw.pinMode=PIN_STATUS_INPUT_PD;
				break;

			default:
				break;
		}

		sw.GPIONum=switches[itr].port;
		sw.pinNum=switches[itr].pin;
		GPIO_initPin(sw);

	}
	return errorStatus;
}

u8 SWITCH_getStatus(u8 Copy_sw,u8* Add_status)
{
	u8 errorStatus=0;
	if(Add_status==NULL)
	{

	}
	else
	{
		* Add_status=G_swState[Copy_sw];
	}
	return errorStatus;
}
u8 SWITCH_runnable(void)
{
	u8 Loc_errorStatus;
	u8 itr;
	u8 Loc_swcurrent=0;
	static u8 Loc_swPrev[NUM_OF_SWITCHES]={0};
	static u32  Loc_swCounts[NUM_OF_SWITCHES]={0};
	for(itr=0; itr<NUM_OF_SWITCHES;itr++)
	{
		GPIO_getPinValue(switches[itr].port,switches[itr].pin,& Loc_swcurrent);
		if(Loc_swcurrent==Loc_swPrev[itr])
		{
			Loc_swCounts[itr]++;
		}
		if(Loc_swCounts[itr]==5)
		{
			G_swState[itr]=Loc_swcurrent^switches[itr].connection;
			Loc_swCounts[itr]=0;
		}
		else
		{
			Loc_swCounts[itr]=0;
		}
		Loc_swPrev[itr]=Loc_swcurrent;
	}
	return Loc_errorStatus;

}
