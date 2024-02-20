/*
 * GPIO.h
 *
 *  Created on: Feb 18, 2024
 *      Author: Noha
 */

#ifndef MCAL_INCLUDES_GPIO_H_
#define MCAL_INCLUDES_GPIO_H_

#include <stdio.h>
#include "../../LIB/std_types.h"


#define  GPIOA (volatile void* const)(0x40020000)
#define  GPIOB (volatile void* const)(0x40020400)
#define  GPIOC (volatile void* const)(0x40020800)
#define  GPIOD (volatile void* const)(0x40020C00)
#define  GPIOE (volatile void* const)(0x40021000)
#define  GPIOH (volatile void* const)(0x40021C00)


/*USER INPUTT*/
#define GPIO_PIN_NUM0  0
#define GPIO_PIN_NUM1  1
#define GPIO_PIN_NUM2  2
#define GPIO_PIN_NUM3  3
#define GPIO_PIN_NUM4  4
#define GPIO_PIN_NUM5  5
#define GPIO_PIN_NUM6  6
#define GPIO_PIN_NUM7  7
#define GPIO_PIN_NUM8  8
#define GPIO_PIN_NUM9  9
#define GPIO_PIN_NUM10 10
#define GPIO_PIN_NUM11 11
#define GPIO_PIN_NUM12 12
#define GPIO_PIN_NUM13 13
#define GPIO_PIN_NUM14 14
#define GPIO_PIN_NUM15 15


/*GPIO MODES*/

/*Bit 0, 1 for mode selection(MODER) , Bit 2 for output type(OTYPER), Bit 3,4 for PU an PD selection PUPDR */

#define PIN_STATUS_GP_OUTPUT_PP     0b00001
#define PIN_STATUS_GP_OUTPUT_PP_PU  0b01001
#define PIN_STATUS_GP_OUTPUT_PP_PD  0b10001
#define PIN_STATUS_RESERVED1        0b11001
#define PIN_STATUS_GP_OUTPUT_OD     0b00101
#define PIN_STATUS_GP_OUTPUT_OD_PU  0b01101
#define PIN_STATUS_GP_OUTPUT_OD_PD  0b10101
#define PIN_STATUS_RESERVED2        0b11101

#define PIN_STATUS_AF_OUTPUT_PP     0b00010
#define PIN_STATUS_AF_OUTPUT_PP_PU  0b01010
#define PIN_STATUS_AF_OUTPUT_PP_PD  0b10010
#define PIN_STATUS_RESERVED3        0b11010
#define PIN_STATUS_AF_OUTPUT_OD     0b00110
#define PIN_STATUS_AF_OUTPUT_OD_PU  0b01110
#define PIN_STATUS_AF_OUTPUT_OD_PD  0b10110
#define PIN_STATUS_RESERVED4        0b11110

#define PIN_STATUS_INPUT_FLOATING   0b00000
#define PIN_STATUS_INPUT_PU         0b01000
#define PIN_STATUS_INPUT_PD         0b10000
#define PIN_STATUS_RESERVED5        0b11000

#define PIN_STATUS_ANALOG		    0b00011
#define PIN_STATUS_RESERVED6        0b10011
#define PIN_STATUS_RESERVED7        0b01011
#define PIN_STATUS_RESERVED8        0b11011

#define PIN_SPEED_LOW_SPEED         0b00
#define PIN_SPEED_MEDIUM_SPEED      0b01
#define PIN_SPEED_HIGH_SPEED        0b10
#define PIN_SPEED_VERY_HIGH_SPEED   0b11

#define STATUS_NOK                  0
#define STATUS_OK                   1
#define STATUS_NOT_VALID_MODE       2
#define STATUS_NULL_POINTER         3

#define VALUE_SET_HIGH              1
#define VALUE_SET_LOW               0

typedef struct
{
	void* GPIONum;
	u8 pinNum;
	u8 pinMode;
	u8 pinSpeed;
}GPIO_pin_t;



u8 GPIO_initPin(GPIO_pin_t copy_GPIO_pin);
u8 GPIO_setPinValue(void* copy_GPIO_portNum, u8 copy_GPIO_pinNum, u8 copy_GPIO_valueSet);
u8 GPIO_getPinValue(void* copy_GPIO_portNum, u8 copy_GPIO_pinNum,u8* Add_GPIO_pinValue);




#endif /* MCAL_INCLUDES_GPIO_H_ */
