/*
 * LED.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Noha
 */

#ifndef HAL_INCLUDES_LED_H_
#define HAL_INCLUDES_LED_H_

#include <stdio.h>
#include "../../LIB/std_types.h"
#include "../../MCAL/INCLUDES/GPIO.h"
#include "LED_cfg.h"


#define CONNECTION_FORWARD 0
#define CONNECTION_REVESE  1

#define LED_ON 1
#define LED_OFF 0

typedef struct
{
	void* port;
	u8 pin;
	u8 connection;
	u8 state;
}LED_cfg_t;



/*in this function we configure the pin modes for ex to be output and its speed */
u8 LED_init(void);
/*here we set the state and connection*/
u8 LED_setState(u32 Copy_led, u8 Copy_state );

#endif /* HAL_INCLUDES_LED_H_ */
