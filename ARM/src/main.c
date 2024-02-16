#include "./MCAL/INCLUDES/RCC.h"


void main (void)
{
	//pllm=50
	//plln=300
	//pllp=2
	RCC_ConfigurePLL(clk_Source_HSI,60,2,400);

	int x=0;

	while(1)
	{

	}
}
