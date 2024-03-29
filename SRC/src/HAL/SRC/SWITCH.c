/*
 * SWITCH.c
 *
 *  Created on: Feb 21, 2024
 *      Author: Noha
 */
#include "../INCLUDES/SWITCH.h"
extern const SWITCH_cfg_t switches[NUM_OF_SWITCHES];
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
	GPIO_getPinValue(switches[Copy_sw].port, switches[Copy_sw].pin,Add_status);
	*Add_status^=switches[Copy_sw].connection;
	return errorStatus;
}






