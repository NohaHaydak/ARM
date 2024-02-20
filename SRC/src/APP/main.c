#include "../MCAL/INCLUDES/RCC.h"


void main (void)
{
	u8 pllm=60;
	u32 plln=300;
	u8 pllp=2;
	RCC_ControlClk(clk_HSE, clk_Status_ON);
	RCC_ConfigureSysclk(clk_HSE);
	RCC_ConfigurePLL(clk_Source_HSE,pllm,pllp,plln);
	RCC_ControlClk(clk_PLL,clk_Status_ON);
	RCC_ConfigureSysclk(clk_PLL);
	RCC_ConfigurePrescaler(peripheral_GPIOA,4,2);
	RCC_ControlPeripheral(peripheral_GPIOA,peri_status_enabled);
	int x=5;
	while(1)
	{

	}
}
