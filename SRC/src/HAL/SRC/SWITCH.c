/*
 * SWITCH.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Noha
 */
#include "../INCLUDES/SWITCH.h"
extern const SWITCH_cfg_t SWITCHES[NUM_OF_SWITCHES];
u8 SWITCH_init(void)
{
	u8 errorStatus=0;
	GPIO_pin_t sw;
	PIN_STATUS_GP_OUTPUT_PP_PU;
	sw.pinSpeed=PIN_SPEED_HIGH_SPEED;
	for(u32 itr=0; itr<NUM_OF_SWITCHES; itr++)
	{
		if(SWITCHES[itr].connection==CONNECTION_PU)
		{
			sw.pinMode=PIN_STATUS_INPUT_PU;
		}
		else if(SWITCHES[itr].connection==CONNECTION_PD)
		{
			sw.pinMode=PIN_STATUS_INPUT_PD;
		}

		sw.GPIONum=SWITCHES[itr].port;
		sw.pinNum=SWITCHES[itr].pin;
		GPIO_initPin(sw);

	}
	return errorStatus;
}

u8 SWITCH_getStatus(u8 Copy_sw,u8* Add_status)
{

	u8 errorStatus=0;
	GPIO_getPinValue(SWITCHES[Copy_sw].port, SWITCHES[Copy_sw].pin,Add_status);
	*Add_status=(SWITCHES[Copy_sw].connection)|(*Add_status);
	return errorStatus;
}






