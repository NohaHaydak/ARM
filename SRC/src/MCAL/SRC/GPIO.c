/*
 * GPIO.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Noha
 */
#include "../INCLUDES/GPIO.h"
#define WRITE_MODE_MASK_MODER    0b00011
#define OD_PP_WRITE_MASK_OTYPER  0b00100
#define PD_PU_WRITE_MASK_OSPEEDR 0b11000
#define OD_PP_BIT_NUM            2
#define PU_PD_BIT_NUM            3

typedef struct
{
	u32 GPIOx_MODER;
	u32 GPIOx_OTYPER;
	u32 GPIOx_OSPEEDR;
	u32 GPIOx_PUPDR;
	u32 GPIOx_IDR;
	u32 GPIOx_ODR;
	u32 GPIOx_BSRR;
	u32 GPIOx_LCKR;
	u32 GPIOx_AFRL;
	u32 GPIOx_AFRH;
}GPIO_t;

u8 GPIO_initPin(GPIO_pin_t copy_GPIO_pin)
{
	/*loc pin is for registers in which each pin is presented by 2 bits*/
	u8 LOC_pin=copy_GPIO_pin.pinNum *2;
	u8 LOC_speed=0;
	u8 LOC_mode=0;
	u8 LOC_PP_OD;
	u8 LOC_PU_PD;
	u8 errorStatus=STATUS_NOK;
	if (copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED1||copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED2||copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED3||copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED4||copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED5||copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED6||copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED7||copy_GPIO_pin.pinMode==PIN_STATUS_RESERVED8)
	{
		errorStatus=STATUS_NOT_VALID_MODE;
	}
	else
	{
		/*extract mode from the user input value as bit 0 and 1 should be assigned in MODER*/
		LOC_mode=copy_GPIO_pin.pinMode& WRITE_MODE_MASK_MODER;
		/*clear bit before assignation*/
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_MODER&= ~(1<<LOC_pin);
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_MODER&= ~(1<<(LOC_pin +1));
		/*assign extracted mode in GPIOx_MODER*/
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_MODER |=((u32)LOC_mode<<LOC_pin);

		/*extract PP or OD from the user input value as bit 2 should be assigned in OTYPER*/
		LOC_PP_OD=copy_GPIO_pin.pinMode& OD_PP_WRITE_MASK_OTYPER;
		LOC_PP_OD=LOC_PP_OD>>OD_PP_BIT_NUM;
		/*clear bit before assignation*/
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_OTYPER &= ~(1<<copy_GPIO_pin.pinNum);
		/*assign extracted PP or OD in GPIOx_OTYPER*/
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_OTYPER |= ((u32)LOC_PP_OD<<copy_GPIO_pin.pinNum);

		/*extract PU or PD from the user input value as bit 3,4 should be assigned in PUPDR*/
		LOC_PU_PD=copy_GPIO_pin.pinMode& PD_PU_WRITE_MASK_OSPEEDR;
		LOC_PU_PD=LOC_PU_PD>>PU_PD_BIT_NUM;
		/*MASKING TO CLEAR THE DESIRED BITS*/
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_PUPDR&= ~(1<<LOC_pin);
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_PUPDR&= ~(1<<(LOC_pin +1));
		/*assign extracted mode in GPIOx_MODER*/
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_PUPDR |= ((u32)LOC_PU_PD<<LOC_pin);

		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_OSPEEDR&= ~(1<<LOC_pin);
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_OSPEEDR&= ~(1<<(LOC_pin +1));
		LOC_speed=copy_GPIO_pin.pinSpeed;
		((volatile GPIO_t* const)copy_GPIO_pin.GPIONum)->GPIOx_OSPEEDR|= ((u32)LOC_speed<<LOC_pin);
		errorStatus=STATUS_OK;

	}


	return errorStatus;

}

u8 GPIO_setPinValue(void* copy_GPIO_portNum, u8 copy_GPIO_pinNum, u8 copy_GPIO_valueSet)
{
	u8 errorStatus= STATUS_NOK;
	u8 LOC_ResetpinNum= copy_GPIO_pinNum+16;
	if (copy_GPIO_portNum==NULL)
	{
		errorStatus= STATUS_NULL_POINTER;
	}
	else
	{
		switch(copy_GPIO_valueSet)
		{
			case VALUE_SET_HIGH:
				(((GPIO_t *)copy_GPIO_portNum)->GPIOx_BSRR)|=(1<<copy_GPIO_pinNum);
				break;

			case VALUE_SET_LOW:
				(((GPIO_t *)copy_GPIO_portNum)->GPIOx_BSRR)|=(1<<LOC_ResetpinNum);
				break;
		}
		errorStatus=STATUS_OK;
	}
	return errorStatus;
}

u8 GPIO_getPinValue(void* copy_GPIO_portNum, u8 copy_GPIO_pinNum,u8* Add_GPIO_pinValue)
{
	u8 errorStatus= STATUS_NOK;
	if (copy_GPIO_portNum==NULL)
	{
		errorStatus= STATUS_NULL_POINTER;
	}
	else
	{
		* Add_GPIO_pinValue=(((((GPIO_t *)copy_GPIO_portNum)->GPIOx_IDR)>>copy_GPIO_pinNum)&1);
		errorStatus=STATUS_OK;
	}
	return errorStatus;
}



