/*
 * HRCC_cfg.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Nada
 */

#include "HRCC_cfg.h"
#include "RCC.h"

/* Offsets */

#define AHB2_OFFSET         9
#define APB1_OFFSET         10
#define APB2_OFFSET         22

/* Implementations */

u8 HRCC_EnablePeriphral (u8 Periphral_Name)
{
    u8 ErrorStatus = Ok;

    switch (Periphral_Name)
    {
        case GPIOAEN...DMA2EN:
            RCC_EnableAHB1Peri(Periphral_Name);
            break;
        case OTGFSEN:
            RCC_EnableAHB2Peri(Periphral_Name - AHB2_OFFSET);
            break;
        case TIM2EN...PWREN:
            RCC_EnableAPB1Peri(Periphral_Name - APB1_OFFSET);
            break;
        case TIM1EN...TIM11EN:
            RCC_EnableAPB2Peri(Periphral_Name - APB2_OFFSET);
            break;
        default:
            ErrorStatus = WrongChoice;
            break;
    }
}

u8 HRCC_DisablePeriphral (u8 Periphral_Name)
{
    u8 ErrorStatus = Ok;

    switch (Periphral_Name)
    {
        case GPIOAEN...DMA2EN:
            RCC_DisableAHB1Peri(Periphral_Name);
            break;
        case OTGFSEN:
            RCC_DisableAHB2Peri(Periphral_Name - AHB2_OFFSET);
            break;
        case TIM2EN...PWREN:
            RCC_DisableAPB1Peri(Periphral_Name - APB1_OFFSET);
            break;
        case TIM1EN...TIM11EN:
            RCC_DisableAPB2Peri(Periphral_Name - APB2_OFFSET);
            break;
        default:
            ErrorStatus = WrongChoice;
            break;
    }
}