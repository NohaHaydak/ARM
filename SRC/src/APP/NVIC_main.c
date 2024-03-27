/*
 * NVIC_APP.c
 *
 *  Created on: Mar 25, 2024
 *      Author: Noha
 */

#include "../MCAL/INCLUDES/NVIC.h"


void main(void)
{
	int x=2;
	NVIC_EnablePriINTR(NVIC_EXT0_INTERRRUPT);
	NVIC_EnablePriINTR(NVIC_EXT1_INTERRRUPT);
	NVIC_DisablePriINTR(NVIC_EXT0_INTERRRUPT);
	NVIC_SetPendingForSw_INTR(NVIC_EXT0_INTERRRUPT);
	NVIC_SetPendingForSw_INTR(NVIC_EXT1_INTERRRUPT);
	NVIC_SetPriority(NVIC_EXT0_INTERRRUPT ,10 , 1);
	x++;
	while(1)
	{

	}
}


