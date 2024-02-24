/*
 * RCC.c
 *
 *  Created on: Feb 15, 2024
 *      Author: Noha
 */


#include "../INCLUDES/RCC.h"
#define RCC_BASE_ADDRESS 0x40023800

/*CONTROL REG (RCC_CR) BITS*/
#define RCC_controlReg_HSION     0
#define RCC_controlReg_HSIRDY    1
#define RCC_controlReg_HSITRIM   3
#define RCC_controlReg_HSICAL    8
#define RCC_controlReg_HSEON     16
#define RCC_controlReg_HSERDY    17
#define RCC_controlReg_HSEBYP    18
#define RCC_controlReg_CSSON     19
#define RCC_controlReg_PLLON     24
#define RCC_controlReg_PLLRDY    25
#define RCC_controlReg_PLLI2SON  26
#define RCC_controlReg_PLLI2SRDY 27

/*PLL CONFIGURATION (RCC_PLLCFGR) BITS*/

/*Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock*/
#define RCC_PLLConfigrationReg_PLLM0  0
#define RCC_PLLConfigrationReg_PLLM1  1
#define RCC_PLLConfigrationReg_PLLM2  2
#define RCC_PLLConfigrationReg_PLLM3  3
#define RCC_PLLConfigrationReg_PLLM4  4
#define RCC_PLLConfigrationReg_PLLM5  5
/*Main PLL (PLL) multiplication factor for VCO*/
#define RCC_PLLConfigrationReg_PLLN   6
/*Main PLL (PLL) division factor for main system clock*/
#define RCC_PLLConfigrationReg_PLLP0  16
#define RCC_PLLConfigrationReg_PLLP1  17
/*Main PLL(PLL) and audio PLL (PLLI2S) entry clock source*/
#define RCC_PLLConfigrationReg_PLLSRC 22
/*Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks*/
#define RCC_PLLConfigrationReg_PLLQ0  24
#define RCC_PLLConfigrationReg_PLLQ1  25
#define RCC_PLLConfigrationReg_PLLQ2  26
#define RCC_PLLConfigrationReg_PLLQ3  27


/*RCC CLOCK CONFIGURATION REGISTER BITS (RCC_CFGR)*/
/*System clock switch*/
#define RCC_ConfigrationReg_SW0           0
#define RCC_ConfigrationReg_SW1           1
/*System clock switch status*/
#define RCC_ConfigrationReg_SWS0          2
#define RCC_ConfigrationReg_SWS1          3
/*AHB prescaler*/
#define RCC_ConfigrationReg_HPRE          4
/*APB Low speed prescaler (APB1)*/
#define RCC_ConfigrationReg_PPRE1         10
/*APB high-speed prescaler (APB2)*/
#define RCC_ConfigrationReg_PPRE2         13
/*HSE division factor for RTC clock*/
#define RCC_ConfigrationReg_RTCPRE        16
/*Microcontroller clock output 1*/
#define RCC_ConfigrationReg_MCO1_RESERVED 21
#define RCC_ConfigrationReg_MCO1          22
/*I2S clock selection*/
#define RCC_ConfigrationReg_I2SSCR        23
/*MCO1 prescaler*/
#define RCC_ConfigrationReg_MCO1_PRE      24
/*MCO2 prescaler*/
#define RCC_ConfigrationReg_MCO2_PRE      27
/*Microcontroller clock output 2*/
#define RCC_ConfigrationReg_MCO2_RESERVED 30
#define RCC_ConfigrationReg_MCO2          31




/*RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)*/
#define RCC_AHB1ENR_GPIOAEN 0
#define RCC_AHB1ENR_GPIOBEN 1
#define RCC_AHB1ENR_GPIOCEN 2
#define RCC_AHB1ENR_GPIODEN 3
#define RCC_AHB1ENR_GPIOEEN 4
#define RCC_AHB1ENR_GPIOHEN 7
#define RCC_AHB1ENR_CRCEN   12
#define RCC_AHB1ENR_DMA1EN  21
#define RCC_AHB1ENR_DMA2EN  22


/* RCC_AHB1ENR BITS WRITE MASKING INST 1<<BIT_NUM TO USE IN  BIT MATH OPERATIONS*/
#define GPIOAEN_WRITE_MASK 0x1
#define GPIOBEN_WRITE_MASK 0x2
#define GPIOCEN_WRITE_MASK 0x4
#define GPIODEN_WRITE_MASK 0x8
#define GPIOEEN_WRITE_MASK 0x10
#define GPIOHEN_WRITE_MASK 0x80
#define CRCEN_WRITE_MASK   0x1000
#define DMA1EN_WRITE_MASK  0x200000
#define DMA2EN_WRITE_MASK  0x400000




/* RCC_RC BITS WRITE MASKING INST 1<<BIT_NUM TO USE IN  BIT MATH OPERATIONS*/
#define HSION_WRITE_MASK     0x1
#define HSITRIM_WRITE_MASK   0x80
#define HSEON_WRITE_MASK     0x10000
#define HSEBYP_WRITE_MASK    0x40000
#define CSSON_WRITE_MASK     0x80000
#define PLLON_WRITE_MASK     0x1000000
#define PLLI2SON_WRITE_MASK  0x4000000


/*RCC_CFGR BITS WRITE MASKING INST 1<<BIT_NUM TO USE IN  BIT MATH OPERATIONS*/
/*System clock switch*/
#define SW0_WRITE_MASK           0x1
#define SW1_WRITE_MASK           0x2
#define SW_WRITE_MASK            0xFFFFFFFC
/*AHB prescaler*/
#define HPRE_WRITE_MASK          0xFFFFFF0F
#define HPRE_1_WRITE_MASK		 0b00000000
#define HPRE_2_WRITE_MASK		 0b10000000
#define HPRE_4_WRITE_MASK		 0b10010000
#define HPRE_8_WRITE_MASK		 0b10100000
#define HPRE_16_WRITE_MASK		 0b10110000
#define HPRE_64_WRITE_MASK		 0b11000000
#define HPRE_128_WRITE_MASK		 0b11010000
#define HPRE_256_WRITE_MASK		 0b11100000
#define HPRE_512_WRITE_MASK		 0b11110000
/*APB Low speed prescaler (APB1)*/
/*clear the 3 bits to assign the req value*/
/*11111111111111111110001111111111*/
#define PPRE1_WRITE_MASK         0xFFFFE3FF
/*APB high-speed prescaler (APB2)*/
/*clear the 3 bits to assign the req value*/
/*11111111111111110001111111111111*/
#define PPRE2_WRITE_MASK         0xFFFF1FFF
/*HSE division factor for RTC clock*/
#define RTCPRE_WRITE_MASK        0x10000
/*Microcontroller clock output 1*/
#define MCO1_WRITE_MASK          0x400000
/*I2S clock selection*/
#define I2SSCR_WRITE_MASK        0x800000
/*MCO1 prescaler*/
#define MCO1_PRE_WRITE_MASK      0x1000000
/*MCO2 prescaler*/
#define MCO2_PRE_WRITE_MASK      0x8000000
/*Microcontroller clock output 2*/
#define MCO2_WRITE_MASK          0x80000000


/*RCC_PLLCFGR BITS WRITE MASKING INST 1<<BIT_NUM TO USE IN  BIT MATH OPERATIONS*/
/*Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock*/
#define PLLM0_WRITE_MASK  0x1
#define PLLM1_WRITE_MASK  0x2
#define PLLM2_WRITE_MASK  0x4
#define PLLM3_WRITE_MASK  0x8
#define PLLM4_WRITE_MASK  0x10
#define PLLM5_WRITE_MASK  0x20

#define PLLM_WRITE_MASK   0xFFFFFFC0
/*Main PLL (PLL) multiplication factor for VCO*/
#define PLLN0_WRITE_MASK  0x40

#define PLLN_WRITE_MASK   0xFFFF803F
/*Main PLL (PLL) division factor for main system clock*/
#define PLLP_WRITE_MASK   0xFFFCFFFF
#define PLLP0_WRITE_MASK  0x10000
#define PLLP1_WRITE_MASK  0x20000
/*Main PLL(PLL) and audio PLL (PLLI2S) entry clock source*/
#define PLLSRC_WRITE_MASK 0xFFBFFFFF
/*Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks*/
#define PLLQ0_WRITE_MASK  0x1000000
#define PLLQ1_WRITE_MASK  0x2000000
#define PLLQ2_WRITE_MASK  0x4000000
#define PLLQ3_WRITE_MASK  0x8000000



typedef struct
{
	u32 RCC_CR;
	u32 RCC_PLLCFGR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;
	u32 Reserved15;
	u32 RCC_DCKCFGR;

}RCC_T;



/*data we are pointing to is volatile but the address itself is const */
static volatile RCC_T * const RCC=(volatile RCC_T * const )RCC_BASE_ADDRESS;

u8 RCC_ControlClk(RCC_clk_t MCopy_clk ,RCC_clk_Status_t MCopy_clk_Status)
{
	u8 LOC_errorStatus=0;
	switch(MCopy_clk)
	{
		case clk_HSE:
			switch(MCopy_clk_Status)
			{
				case clk_Status_ON:
					/*clear HSEBYP and enable HSE oscillator*/
					RCC->RCC_CR &= ~(HSEBYP_WRITE_MASK);
					RCC->RCC_CR|=HSEON_WRITE_MASK;
					break;
				case clk_Status_OFF:
					RCC->RCC_CR &= ~(HSEON_WRITE_MASK);
					break;
			}

			break;

		case clk_HSEBYP:
			switch(MCopy_clk_Status)
			{
				case clk_Status_ON:
					/* disable HSE oscillator while setting HSEBYP*/

					RCC->RCC_CR|=HSEON_WRITE_MASK;
					RCC->RCC_CR|=HSEBYP_WRITE_MASK;
					break;
				case clk_Status_OFF:
					RCC->RCC_CR &= ~(HSEBYP_WRITE_MASK);
					break;
			}

			break;

		case clk_HSI:
			switch(MCopy_clk_Status)
			{
				case clk_Status_ON:
					RCC->RCC_CR|=HSITRIM_WRITE_MASK;;
					RCC->RCC_CR|=HSION_WRITE_MASK;
					break;
				case clk_Status_OFF:
					RCC->RCC_CR &= ~(HSION_WRITE_MASK);
					break;
			}

			break;

		case clk_PLL:
			switch(MCopy_clk_Status)
			{
				case clk_Status_ON:
					RCC->RCC_CR|=PLLON_WRITE_MASK;
					break;
				case clk_Status_OFF:
					RCC->RCC_CR &= ~(PLLON_WRITE_MASK);
					break;
			}

			break;

		default:
			break;

	}
	return LOC_errorStatus;
}


u8 RCC_ConfigureSysclk(RCC_clk_t MCopyclk)
{
	u8 LOC_errorStatus=0;
	u16 LOC_time_out=1000;

	switch(MCopyclk)
	{
		case clk_HSI:
			/*wait till ready flag is set then choose it as sysclk*/
			while(!(1&(RCC->RCC_CR>>RCC_controlReg_HSIRDY))&&LOC_time_out)
			{
				LOC_time_out--;
			}
			if ((1&(RCC->RCC_CR>>RCC_controlReg_HSIRDY))==1)
			{
				/*00 is selecting HSI as sysclk*/
				RCC->RCC_CFGR &=SW_WRITE_MASK;
				RCC->RCC_CFGR|=0x00000000;
			}
			break;

		case clk_HSE:
			while(!(1&(RCC->RCC_CR>>RCC_controlReg_HSERDY))&&LOC_time_out)
			{
				LOC_time_out--;
			}
			if ((1&(RCC->RCC_CR>>RCC_controlReg_HSERDY))==1)
			{
				/*01 is selecting HSE as sysclk*/
				RCC->RCC_CFGR &=SW_WRITE_MASK;
				RCC->RCC_CFGR |=0x00000001;
			}
			break;

		case clk_HSEBYP:
			while(!(1&(RCC->RCC_CR>>RCC_controlReg_HSERDY))&&LOC_time_out)
			{
				LOC_time_out--;
			}
			if ((1&(RCC->RCC_CR>>RCC_controlReg_HSERDY))==1)
			{
				/*01 is selecting HSEBYP as sysclk*/
				RCC->RCC_CFGR &=SW_WRITE_MASK;
				RCC->RCC_CFGR |=0x00000001;
			}
			break;

		case clk_PLL:
			while(!(1&(RCC->RCC_CR>>RCC_controlReg_PLLRDY))&&LOC_time_out)
			{
				LOC_time_out--;
			}
			if ((1&(RCC->RCC_CR>>RCC_controlReg_PLLRDY))==1)
			{
				/*10 is selecting PLL as sysclk*/
				RCC->RCC_CFGR &=SW_WRITE_MASK;
				RCC->RCC_CFGR|=0x00000002;
			}
			break;

		default:
			break;
	}
	/*if sw is 11 then return not applicable*/
	/*if ()
	{
	}
	if()
	{
		/*sws not eq sw*/
	/*}*/
	return LOC_errorStatus;
}

u8 RCC_ConfigurePLL(u8 MCopy_clk_Source,u8 MCopy_PLLM_factor,u8 MCopy_PLLP_factor,u16 MCopy_PLLN_factor)
{
	u8 LOC_errorStatus=0;
	u8 Sysclk_reading0;
	u8 Sysclk_reading1;
	Sysclk_reading0= (RCC->RCC_CFGR>>RCC_ConfigrationReg_SWS0)&1;
	Sysclk_reading1= (RCC->RCC_CFGR>>RCC_ConfigrationReg_SWS1)&1;
	/*check if pll is selected as sysclk don't allow the configuration and return error status*/
	if (Sysclk_reading0==0 && Sysclk_reading1==1)
	{
		LOC_errorStatus=PLL_IS_SELECTED_AS_SYSCLK_PLEASE_SWITCH_BEFORE_CONFIG;
	}
	/*192 ?PLLN ?432*/
	else if(MCopy_PLLN_factor>432 || MCopy_PLLN_factor<192)
	{
		LOC_errorStatus= PLLN_IS_OUT_OF_RANGE;
	}
	/*2 ?PLLM ?63*/
	else if (MCopy_PLLM_factor<2 || MCopy_PLLM_factor>63)
	{
		LOC_errorStatus= PLLM_IS_OUT_OF_RANGE;
	}
	else
	{


		/*clk source*/
		RCC->RCC_PLLCFGR &= PLLSRC_WRITE_MASK;
		RCC->RCC_PLLCFGR |=((u32)MCopy_clk_Source);

		/*PLLP*/
		RCC->RCC_PLLCFGR &= PLLP_WRITE_MASK;
		RCC->RCC_PLLCFGR|=((u32)MCopy_PLLP_factor<<RCC_PLLConfigrationReg_PLLP0);

		/*PLLM*/
		/*masking and assigning value in register*/
		RCC->RCC_PLLCFGR &= PLLM_WRITE_MASK;
		RCC->RCC_PLLCFGR|=(u32)MCopy_PLLM_factor;
		/*PLLN*/
		/*masking and assigning value in register*/
		RCC->RCC_PLLCFGR &=PLLN_WRITE_MASK;
		RCC->RCC_PLLCFGR |= (u32)(MCopy_PLLN_factor<<RCC_PLLConfigrationReg_PLLN);

	}

	return LOC_errorStatus;
}




/*configure prescaler for each peripheral*/
u8 RCC_ConfigurePrescaler(u8 MCopy_APB1prescalerValue ,u8 MCopy_APB2prescalerValue ,u16 MCopy_AHBprescalerValue)
{
	u8 LOC_errorStatus=0;
	/*AHB MUST BE SET AT FIRST AS IT'S AN INPUT TO APB PRESCALER*/
	RCC->RCC_CFGR &= HPRE_WRITE_MASK;
	RCC->RCC_CFGR |=((u32)MCopy_AHBprescalerValue);

	/*APB1 LOW SPEEDS*/
	RCC->RCC_CFGR &=PPRE1_WRITE_MASK;
	RCC->RCC_CFGR |=((u32)MCopy_APB1prescalerValue);

	/*APB2 HIGH SPEEDS*/
	RCC->RCC_CFGR &=PPRE2_WRITE_MASK;
	RCC->RCC_CFGR |=((u32)MCopy_APB2prescalerValue);

	return LOC_errorStatus;
}

/*control (on/off) any peripheral*/
u8 RCC_ControlPeripheral(RCC_peripheral_t MCopy_peripheral ,RCC_peripheral_status_t MCopy_peri_status)
{
	u8 LOC_errorStatus=0;
	switch(MCopy_peripheral)
	{
		/*AHB2*/
		case peripheral_USB_OTG_FS:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					break;
				case peri_status_disabled:
					break;
			}
			break;
		/*AHB1*/

		case peripheral_GPIOA:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=GPIOAEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOAEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_GPIOB:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=GPIOBEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_GPIOC:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=GPIOCEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_GPIOD:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=GPIODEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_GPIOE:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=GPIOEEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_GPIOH:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=GPIOHEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_CRC:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=CRCEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_DMA2:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=DMA2EN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;
		case peripheral_DMA1:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=DMA1EN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(GPIOBEN_WRITE_MASK);
					break;
			}
			break;

		/*APB2*/
		/*case peripheral_EXTI:
			switch(MCopy_peri_status)
			{
				case peri_status_enabled:
					RCC->RCC_AHB1ENR|=EXTIEN_WRITE_MASK;
					break;
				case peri_status_disabled:
					RCC->RCC_AHB1ENR&=~(EXTIEN_WRITE_MASK);
					break;
			}
			break;*/
	}

	if (MCopy_peripheral==peripheral_USB_OTG_FS)
	{

	}


	else if(MCopy_peripheral>=peripheral_DMA2 &&MCopy_peripheral<peripheral_PWR)
	{

	}
	/*APB1*/
	else if (MCopy_peripheral>=peripheral_PWR &&MCopy_peripheral<=peripheral_TIM2)
	{

	}
	/*APB2*/
	else
	{

	}

	return LOC_errorStatus;
}

