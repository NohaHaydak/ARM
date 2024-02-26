#include "../MCAL/INCLUDES/RCC.h"


void main (void)
{
	u8 pllm=60;
	u32 plln=300;
	RCC_ControlClk(clk_HSE, clk_Status_ON);
	RCC_ConfigureSysclk(clk_HSE);
	RCC_ConfigurePLL(clk_Source_HSE,pllm,PLLP_FACTOR4,plln);
	RCC_ControlClk(clk_PLL,clk_Status_ON);
	RCC_ConfigureSysclk(clk_PLL);
	//RCC_ConfigurePrescaler(APB_PRESCALER_VALUE_2,APB_PRESCALER_VALUE_2,AHB_PRESCALER_VALUE_2);
	//RCC_ControlPeripheral(peripheral_GPIOA,peri_status_enabled);
	int x=5;
	while(1)
	{

	}
}
