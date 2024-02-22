/*
 * SWITCH.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Noha
 */

#ifndef HAL_INCLUDES_SWITCH_H_
#define HAL_INCLUDES_SWITCH_H_

#include <stdio.h>
#include "../../LIB/std_types.h"
#include "../../MCAL/INCLUDES/GPIO.h"
#include "SWITCH_cfg.h"


#define CONNECTION_PU 1
#define CONNECTION_PD 0

#define SWITCH_PRESSED 1
#define SWITCH_NOT_PRESSED 0
typedef struct
{
	void* port;
	u8 pin;
	/*PULL UP OR DOWN*/
	u8 connection;
}SWITCH_cfg_t;



/*in this function we configure the pin modes for ex to be input and its speed */
u8 SWITCH_init(void);
/*here we set the state and connection*/
u8 SWITCH_getStatus(u8 Copy_sw,u8* Add_status);


#endif /* HAL_INCLUDES_SWITCH_H_ */
