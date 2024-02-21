/*
 * GPIO_app.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Noha
 */

#include "../MCAL/INCLUDES/GPIO.h"
#include "../MCAL/INCLUDES/RCC.h"

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

	/*testing gpio*/
	GPIO_initPin(pin);

	while(1)
	{
		GPIO_setPinValue(GPIOA, GPIO_PIN_NUM7,VALUE_SET_HIGH );

	}
}

