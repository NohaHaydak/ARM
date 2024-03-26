/*
 * NVIC_APP.c
 *
 *  Created on: Mar 25, 2024
 *      Author: Noha
 */

#include "../MCAL/INCLUDES/NVIC.h"


void main(void)
{

	NVIC_EnablePriINTR(NVIC_EXT0_INTERRRUPT);
	NVIC_SetPendingForSw_INTR(NVIC_EXT0_INTERRRUPT);
	while(1)
	{

	}
}


