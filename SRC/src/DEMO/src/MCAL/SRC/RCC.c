/*
 * RCC.c
 *
 *  Created on: Feb 7, 2024
 *      Author: Nada
 */

#include <RCC.h>

/* Registers base address */
#define RCC_BASEADD				0x40023800

/* Clocks Frequency */
#define HSI_FREQUENCY			16
#define HSE_FREQUENCY			26
#define MAX_FREQUENCY			84

/* RCC Registers */
typedef struct
{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 Reserved1;
	volatile u32 Reserved2;
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 Reserved3;
	volatile u32 Reserved4;
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 Reserved5;
	volatile u32 Reserved6;
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 Reserved7;
	volatile u32 Reserved8;
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 Reserved9;
	volatile u32 Reserved10;
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 Reserved11;
	volatile u32 Reserved12;
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 Reserved13;
	volatile u32 Reserved14;
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 Reserved15;
	volatile u32 RCC_DCKCFGR;
}Registers_t;

/* RCC_CR masks */
#define RCC_CR_RESET			0x00000081
#define RCC_CR_HSI				0x00000001
#define RCC_CR_HSE				0x00010000
#define RCC_CR_PLL				0x01000000

#define HSIRDY_BIT				1
#define HSERDY_BIT				17
#define PLLRDY_BIT				25

/* RCC_PLLCFGR masks */
#define RCC_PLLCFGR_RESET		0x24003010
#define RCC_PLLCFGR_SRC			0x00400000
#define RCC_PLLCFGR_SRC_SHIFTING 22

#define RCC_PLLCFGR_M_CLR		0xFFFFFFC0
#define RCC_PLLCFGR_M_MIN		2
#define RCC_PLLCFGR_M_MAX		63

#define RCC_PLLCFGR_N_CLR		0xFFFF803F
#define RCC_PLLCFGR_N_MIN		192
#define RCC_PLLCFGR_N_MAX		432
#define RCC_PLLCFGR_N_SHIFTING	6

#define RCC_PLLCFGR_P_CLR		0xFFFCFFFF
#define RCC_PLLCFGR_P_2			2
#define RCC_PLLCFGR_P_4			4
#define RCC_PLLCFGR_P_6			6
#define RCC_PLLCFGR_P_8			8
#define RCC_PLLCFGR_P_VALUE2	0
#define RCC_PLLCFGR_P_VALUE4	1
#define RCC_PLLCFGR_P_VALUE6	2
#define RCC_PLLCFGR_P_VALUE8	3
#define RCC_PLLCFGR_P_SHIFTING	16

#define RCC_PLLCFGR_Q_CLR		0xF0FFFFFF
#define RCC_PLLCFGR_Q_MIN		2
#define RCC_PLLCFGR_Q_MAX		15
#define RCC_PLLCFGR_Q_SHIFTING	24


/* RCC_CFGR masks */
#define RCC_CFGR_SW_CLR			0xFFFFFFFC
#define RCC_CFGR_SW_HSI			0x00000000
#define RCC_CFGR_SW_HSE			0x00000001
#define RCC_CFGR_SW_PLL			0x00000002
#define RCC_CFGR_SW_NA			0x00000003

#define RCC_CFGR_SWS			0x0000000C
#define RCC_CFGR_SWS_SHIFTING	2

/* RCC_AHB1ENR masks */
#define RCC_AHB1ENR_RESET		0x00000000

#define RCC_AHB1ENR_GPIOAEN		0x00000001
#define RCC_AHB1ENR_GPIOBEN		0x00000002
#define RCC_AHB1ENR_GPIOCEN		0x00000004
#define RCC_AHB1ENR_GPIODEN		0x00000008
#define RCC_AHB1ENR_GPIOEEN		0x00000010
#define RCC_AHB1ENR_GPIOHEN		0x00000080
#define RCC_AHB1ENR_CRCEN		0x00001000
#define RCC_AHB1ENR_DMA1EN		0x00200000
#define RCC_AHB1ENR_DMA2EN		0x00400000


/* RCC_AHB2ENR masks */
#define RCC_AHB2ENR_RESET		0x00000000

#define RCC_AHB2ENR_OTGFSEN		0x00000080

/* RCC_APB1ENR masks */
#define RCC_APB1ENR_RESET		0x00000000

#define RCC_APB1ENR_TIM2EN		0x00000001
#define RCC_APB1ENR_TIM3EN		0x00000002
#define RCC_APB1ENR_TIM4EN		0x00000004
#define RCC_APB1ENR_TIM5EN		0x00000008
#define RCC_APB1ENR_WWDGEN		0x00000800
#define RCC_APB1ENR_SPI2EN		0x00004000
#define RCC_APB1ENR_SPI3EN		0x00008000
#define RCC_APB1ENR_USART2EN	0x00020000
#define RCC_APB1ENR_I2C1EN		0x00200000
#define RCC_APB1ENR_I2C2EN		0x00400000
#define RCC_APB1ENR_I2C3EN		0x00800000
#define RCC_APB1ENR_PWREN		0x10000000



/* RCC_APB2ENR masks */
#define RCC_APB2ENR_RESET		0x00000000

#define RCC_APB2ENR_TIM1EN		0x00000001
#define RCC_APB2ENR_USART1EN	0x00000010
#define RCC_APB2ENR_USART6EN	0x00000020
#define RCC_APB2ENR_ADC1EN		0x00000100
#define RCC_APB2ENR_SDIOEN		0x00000800
#define RCC_APB2ENR_SPI1EN		0x00001000
#define RCC_APB2ENR_SPI4EN		0x00002000
#define RCC_APB2ENR_SYSCFGEN	0x00004000
#define RCC_APB2ENR_TIM9EN		0x00010000
#define RCC_APB2ENR_TIM10EN		0x00020000
#define RCC_APB2ENR_TIM11EN		0x00040000

/* On or Off */
#define OFF			0
#define ON			1

Registers_t *RCC_Regs = (Registers_t*)RCC_BASEADD;

/* Static Function */
static u8 RCC_GetPLLSource (void)
{
	u32 Loc_CopyReg = RCC_Regs->RCC_PLLCFGR;

	//Reading Bit22

	return (((Loc_CopyReg)&RCC_PLLCFGR_SRC)>>RCC_PLLCFGR_SRC_SHIFTING);
}

/* Implementations */
u8 RCC_EnableClk (RCC_Clock_t Clock)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_CR;

	switch (Clock)
	{
		case Clock_HSI:
			Loc_CopyReg |= RCC_CR_HSI;
			break;
		case Clock_HSE:
			Loc_CopyReg |= RCC_CR_HSE;
			break;
		case Clock_PLL:
			Loc_CopyReg |= RCC_CR_PLL;
			break;
		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_CR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_DisableClk (RCC_Clock_t Clock)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_CR;

	switch (Clock)
	{
		case Clock_HSI:
			Loc_CopyReg &= ~RCC_CR_HSI;
			break;
		case Clock_HSE:
			Loc_CopyReg &= ~RCC_CR_HSE;
			break;
		case Clock_PLL:
			Loc_CopyReg &= ~RCC_CR_PLL;
			break;
		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_CR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_SelectSysClk (RCC_Clock_t Clock)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_CFGR;

	switch (Clock)
	{
		case Clock_HSI:
			Loc_CopyReg &= RCC_CFGR_SW_CLR;
			Loc_CopyReg |= RCC_CFGR_SW_HSI;
			break;
		case Clock_HSE:
			Loc_CopyReg &= RCC_CFGR_SW_CLR;
			Loc_CopyReg |= RCC_CFGR_SW_HSE;
			break;
		case Clock_PLL:
			Loc_CopyReg &= RCC_CFGR_SW_CLR;
			Loc_CopyReg |= RCC_CFGR_SW_PLL;
			break;
		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_CFGR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_CheckClkStatus (RCC_Clock_t Clock, RCC_Status_t *ClockStatus)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_CR;

	switch (Clock)
	{
		case Clock_HSI:
			if (((Loc_CopyReg)>>HSIRDY_BIT)&1)
			{
				*ClockStatus = Ready;
			}
			else
			{
				*ClockStatus = NotReady;
			}
			break;
		case Clock_HSE:
			if (((Loc_CopyReg)>>HSERDY_BIT)&1)
			{
				*ClockStatus = Ready;
			}
			else
			{
				*ClockStatus = NotReady;
			}
			break;
		case Clock_PLL:
			if (((Loc_CopyReg)>>PLLRDY_BIT)&1)
			{
				*ClockStatus = Ready;
			}
			else
			{
				*ClockStatus = NotReady;
			}
			break;
		default:
			ErrorStatus = WrongChoice;
			break;
	}

	return ErrorStatus;
}

u8 RCC_SetPLLSource (RCC_Clock_t Clock)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_PLLCFGR;

	switch (Clock)
	{
		case Clock_HSI:
			Loc_CopyReg &= ~RCC_PLLCFGR_SRC;
			break;
		case Clock_HSE:
			Loc_CopyReg |= RCC_PLLCFGR_SRC;
			break;
		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_PLLCFGR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_ConfigPLL (u32 M, u32 N, u32 P, u32 Q)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_PLLCFGR;

	if (M > RCC_PLLCFGR_M_MAX || M < RCC_PLLCFGR_M_MIN)
		ErrorStatus = NotOk;

	if (N > RCC_PLLCFGR_N_MAX || N < RCC_PLLCFGR_N_MIN)
		ErrorStatus = NotOk;

	if (Q > RCC_PLLCFGR_Q_MAX || Q < RCC_PLLCFGR_Q_MIN)
		ErrorStatus = NotOk;

	u32 Fpll = 0, Fusb = 0;

	switch (RCC_GetPLLSource())
	{
		case Clock_HSI:
			Fpll = HSI_FREQUENCY*N/(M*P);
			Fusb = HSI_FREQUENCY*N/(M*Q);
			break;
		case Clock_HSE:
			Fpll = HSE_FREQUENCY*N/(M*P);
			Fusb = HSE_FREQUENCY*N/(M*Q);
			break;
		default:
			break;
	}

	switch (P)
	{
		case RCC_PLLCFGR_P_2:
			P = RCC_PLLCFGR_P_VALUE2;
			break;
		case RCC_PLLCFGR_P_4:
			P = RCC_PLLCFGR_P_VALUE4;
			break;
		case RCC_PLLCFGR_P_6:
			P = RCC_PLLCFGR_P_VALUE6;
			break;
		case RCC_PLLCFGR_P_8:
			P = RCC_PLLCFGR_P_VALUE8;
			break;
		default:
			ErrorStatus = NotOk;
			break;
	}

	if (ErrorStatus==Ok && Fpll <= 84 && Fusb == 48)
	{
		Loc_CopyReg &= RCC_PLLCFGR_M_CLR;
		Loc_CopyReg |= M;
		Loc_CopyReg &= RCC_PLLCFGR_N_CLR;
		Loc_CopyReg |= (N<<RCC_PLLCFGR_N_SHIFTING);
		Loc_CopyReg &= RCC_PLLCFGR_P_CLR;
		Loc_CopyReg |= (P<<RCC_PLLCFGR_P_SHIFTING);
		Loc_CopyReg &= RCC_PLLCFGR_Q_CLR;
		Loc_CopyReg |= (Q<<RCC_PLLCFGR_Q_SHIFTING);
	}

	RCC_Regs->RCC_PLLCFGR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_EnableAHB1Peri(AHB1ENR_Peri_t AHB1_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_AHB1ENR;

	switch (AHB1_Peri)
	{
		case AHB1ENR_GPIOAEN:
			Loc_CopyReg |= RCC_AHB1ENR_GPIOAEN;
			break;

		case AHB1ENR_GPIOBEN:
			Loc_CopyReg |= RCC_AHB1ENR_GPIOBEN;
			break;

		case AHB1ENR_GPIOCEN:
			Loc_CopyReg |= RCC_AHB1ENR_GPIOCEN;
			break;

		case AHB1ENR_GPIODEN:
			Loc_CopyReg |= RCC_AHB1ENR_GPIODEN;
			break;

		case AHB1ENR_GPIOEEN:
			Loc_CopyReg |= RCC_AHB1ENR_GPIOEEN;
			break;

		case AHB1ENR_GPIOHEN:
			Loc_CopyReg |= RCC_AHB1ENR_GPIOHEN;
			break;

		case AHB1ENR_CRCEN:
			Loc_CopyReg |= RCC_AHB1ENR_CRCEN;
			break;

		case AHB1ENR_DMA1EN:
			Loc_CopyReg |= RCC_AHB1ENR_DMA1EN;
			break;

		case AHB1ENR_DMA2EN:
			Loc_CopyReg |= RCC_AHB1ENR_DMA2EN;
			break;

		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_AHB1ENR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_EnableAHB2Peri(AHB2ENR_Peri_t AHB2_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_AHB2ENR;

	if (AHB2_Peri == AHB2ENR_OTGFSEN)
		Loc_CopyReg |= RCC_AHB2ENR_OTGFSEN;
	else
		ErrorStatus = WrongChoice;

	RCC_Regs->RCC_AHB2ENR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_EnableAPB1Peri(APB1ENR_Peri_t APB1_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_APB1ENR;

	switch (APB1_Peri)
	{
		case APB1ENR_TIM2EN:
			Loc_CopyReg |= RCC_APB1ENR_TIM2EN;
			break;

		case APB1ENR_TIM3EN:
			Loc_CopyReg |= RCC_APB1ENR_TIM3EN;
			break;

		case APB1ENR_TIM4EN:
			Loc_CopyReg |= RCC_APB1ENR_TIM4EN;
			break;

		case APB1ENR_TIM5EN:
			Loc_CopyReg |= RCC_APB1ENR_TIM5EN;
			break;

		case APB1ENR_WWDGEN:
			Loc_CopyReg |= RCC_APB1ENR_WWDGEN;
			break;

		case APB1ENR_SPI2EN:
			Loc_CopyReg |= RCC_APB1ENR_SPI2EN;
			break;

		case APB1ENR_SPI3EN:
			Loc_CopyReg |= RCC_APB1ENR_SPI3EN;
			break;

		case APB1ENR_USART2EN:
			Loc_CopyReg |= RCC_APB1ENR_USART2EN;
			break;

		case APB1ENR_I2C1EN:
			Loc_CopyReg |= RCC_APB1ENR_I2C1EN;
			break;

		case APB1ENR_I2C2EN:
			Loc_CopyReg |= RCC_APB1ENR_I2C2EN;
			break;

		case APB1ENR_I2C3EN:
			Loc_CopyReg |= RCC_APB1ENR_I2C3EN;
			break;

		case APB1ENR_PWREN:
			Loc_CopyReg |= RCC_APB1ENR_PWREN;
			break;

		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_APB1ENR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_EnableAPB2Peri(APB2ENR_Peri_t APB2_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_APB2ENR;

	switch (APB2_Peri)
	{
		case APB2ENR_TIM1EN:
			Loc_CopyReg |= RCC_APB2ENR_TIM1EN;
			break;

		case APB2ENR_USART1EN:
			Loc_CopyReg |= RCC_APB2ENR_USART1EN;
			break;

		case APB2ENR_USART6EN:
			Loc_CopyReg |= APB2ENR_USART6EN;
			break;

		case APB2ENR_ADC1EN:
			Loc_CopyReg |= RCC_APB2ENR_ADC1EN;
			break;

		case APB2ENR_SDIOEN:
			Loc_CopyReg |= RCC_APB2ENR_SDIOEN;
			break;

		case APB2ENR_SPI1EN:
			Loc_CopyReg |= RCC_APB2ENR_SPI1EN;
			break;

		case APB2ENR_SPI4EN:
			Loc_CopyReg |= RCC_APB2ENR_SPI4EN;
			break;

		case APB2ENR_SYSCFGEN:
			Loc_CopyReg |= RCC_APB2ENR_SYSCFGEN;
			break;

		case APB2ENR_TIM9EN:
			Loc_CopyReg |= RCC_APB2ENR_TIM9EN;
			break;

		case APB2ENR_TIM10EN:
			Loc_CopyReg |= RCC_APB2ENR_TIM10EN;
			break;

		case APB2ENR_TIM11EN:
			Loc_CopyReg |= RCC_APB2ENR_TIM11EN;
			break;

		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_APB2ENR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_DisableAHB1Peri(AHB1ENR_Peri_t AHB1_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_AHB1ENR;

	switch (AHB1_Peri)
	{
		case AHB1ENR_GPIOAEN:
			Loc_CopyReg &= ~RCC_AHB1ENR_GPIOAEN;
			break;

		case AHB1ENR_GPIOBEN:
			Loc_CopyReg &= ~RCC_AHB1ENR_GPIOBEN;
			break;

		case AHB1ENR_GPIOCEN:
			Loc_CopyReg &= ~RCC_AHB1ENR_GPIOCEN;
			break;

		case AHB1ENR_GPIODEN:
			Loc_CopyReg &= ~RCC_AHB1ENR_GPIODEN;
			break;

		case AHB1ENR_GPIOEEN:
			Loc_CopyReg &= ~RCC_AHB1ENR_GPIOEEN;
			break;

		case AHB1ENR_GPIOHEN:
			Loc_CopyReg &= ~RCC_AHB1ENR_GPIOHEN;
			break;

		case AHB1ENR_CRCEN:
			Loc_CopyReg &= ~RCC_AHB1ENR_CRCEN;
			break;

		case AHB1ENR_DMA1EN:
			Loc_CopyReg &= ~RCC_AHB1ENR_DMA1EN;
			break;

		case AHB1ENR_DMA2EN:
			Loc_CopyReg &= ~RCC_AHB1ENR_DMA2EN;
			break;

		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_AHB1ENR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_DisableAHB2Peri(AHB2ENR_Peri_t AHB2_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_AHB2ENR;

	if (AHB2_Peri == AHB2ENR_OTGFSEN)
		Loc_CopyReg &= ~RCC_AHB2ENR_OTGFSEN;
	else
		ErrorStatus = WrongChoice;

	RCC_Regs->RCC_AHB2ENR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_DisableAPB1Peri(APB1ENR_Peri_t APB1_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_APB1ENR;

	switch (APB1_Peri)
	{
		case APB1ENR_TIM2EN:
			Loc_CopyReg &= ~RCC_APB1ENR_TIM2EN;
			break;

		case APB1ENR_TIM3EN:
			Loc_CopyReg &= ~RCC_APB1ENR_TIM3EN;
			break;

		case APB1ENR_TIM4EN:
			Loc_CopyReg &= ~RCC_APB1ENR_TIM4EN;
			break;

		case APB1ENR_TIM5EN:
			Loc_CopyReg &= ~RCC_APB1ENR_TIM5EN;
			break;

		case APB1ENR_WWDGEN:
			Loc_CopyReg &= ~RCC_APB1ENR_WWDGEN;
			break;

		case APB1ENR_SPI2EN:
			Loc_CopyReg &= ~RCC_APB1ENR_SPI2EN;
			break;

		case APB1ENR_SPI3EN:
			Loc_CopyReg &= ~RCC_APB1ENR_SPI3EN;
			break;

		case APB1ENR_USART2EN:
			Loc_CopyReg &= ~RCC_APB1ENR_USART2EN;
			break;

		case APB1ENR_I2C1EN:
			Loc_CopyReg &= ~RCC_APB1ENR_I2C1EN;
			break;

		case APB1ENR_I2C2EN:
			Loc_CopyReg &= ~RCC_APB1ENR_I2C2EN;
			break;

		case APB1ENR_I2C3EN:
			Loc_CopyReg &= ~RCC_APB1ENR_I2C3EN;
			break;

		case APB1ENR_PWREN:
			Loc_CopyReg &= ~RCC_APB1ENR_PWREN;
			break;

		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_APB1ENR = Loc_CopyReg;

	return ErrorStatus;
}

u8 RCC_DisableAPB2Peri(APB2ENR_Peri_t APB2_Peri)
{
	u8 ErrorStatus = Ok;

	u32 Loc_CopyReg = RCC_Regs->RCC_APB2ENR;

	switch (APB2_Peri)
	{
		case APB2ENR_TIM1EN:
			Loc_CopyReg &= ~RCC_APB2ENR_TIM1EN;
			break;

		case APB2ENR_USART1EN:
			Loc_CopyReg &= ~RCC_APB2ENR_USART1EN;
			break;

		case APB2ENR_USART6EN:
			Loc_CopyReg &= ~RCC_APB2ENR_USART6EN;
			break;

		case APB2ENR_ADC1EN:
			Loc_CopyReg &= ~RCC_APB2ENR_ADC1EN;
			break;

		case APB2ENR_SDIOEN:
			Loc_CopyReg &= ~RCC_APB2ENR_SDIOEN;
			break;

		case APB2ENR_SPI1EN:
			Loc_CopyReg &= ~RCC_APB2ENR_SPI1EN;
			break;

		case APB2ENR_SPI4EN:
			Loc_CopyReg &= ~RCC_APB2ENR_SPI4EN;
			break;

		case APB2ENR_SYSCFGEN:
			Loc_CopyReg &= ~RCC_APB2ENR_SYSCFGEN;
			break;

		case APB2ENR_TIM9EN:
			Loc_CopyReg &= ~RCC_APB2ENR_TIM9EN;
			break;

		case APB2ENR_TIM10EN:
			Loc_CopyReg &= ~RCC_APB2ENR_TIM10EN;
			break;

		case APB2ENR_TIM11EN:
			Loc_CopyReg &= ~RCC_APB2ENR_TIM11EN;
			break;

		default:
			ErrorStatus = WrongChoice;
			break;
	}

	RCC_Regs->RCC_APB2ENR = Loc_CopyReg;

	return ErrorStatus;
}