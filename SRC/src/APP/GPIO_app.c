/*
 * GPIO_app.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Noha
 */


#include "../MCAL/INCLUDES/RCC.h"
#include "../HAL/INCLUDES/LED.h"
#include "../HAL/INCLUDES/SWITCH.h"
void delay(unsigned int milliseconds);

void main (void)
{
	u16 AHBprescalerValue=2;
	u8 APBprescalerValue=2;
	GPIO_pin_t pin;
	pin.GPIONum=GPIOA;
	pin.pinMode=PIN_STATUS_GP_OUTPUT_PP_PU;
	pin.pinNum=GPIO_PIN_NUM7;
	pin.pinSpeed=PIN_SPEED_MEDIUM_SPEED;
	RCC_ConfigurePrescaler(peripheral_GPIOA ,AHBprescalerValue,APBprescalerValue);
	RCC_ControlPeripheral(peripheral_GPIOA,peri_status_enabled);
	RCC_ControlPeripheral(peripheral_GPIOB,peri_status_enabled);
	RCC_ControlPeripheral(peripheral_GPIOC,peri_status_enabled);
	RCC_ControlPeripheral(peripheral_GPIOD,peri_status_enabled);
	RCC_ControlPeripheral(peripheral_GPIOE,peri_status_enabled);
	RCC_ControlPeripheral(peripheral_GPIOH,peri_status_enabled);

	/*testing led*/
	LED_init();
	SWITCH_init();
	u8 status;
	while(1)
	{
		SWITCH_getStatus(SWITCH_2,& status);
		if(status==SWITCH_PRESSED)
		{SWITCH_getStatus(SWITCH_2,& status);
			delay(200);
			if(status==SWITCH_PRESSED)
					{
						delay(200);
						LED_setState(led_2, LED_ON );

					}
		}

	}
}

void delay(unsigned int milliseconds) {
    unsigned int i, j;

    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 6000; j++) {
            // Adjust the loop count based on your processor speed
            // This loop count may need to be adjusted for different processors
        }
    }
}
