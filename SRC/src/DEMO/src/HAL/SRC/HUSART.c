/*
 * HUSART.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Yasmine Mostafa
 */


#include "STD_Types.h"
#include "Error.h"
#include "RCC.h"
#include "NVIC.h"
#include "GPIO.h"
#include "USART.h"
#include "HUSART_CFG.h"
#include "HUSART.h"

const HUSART_Config_t HUSART_Config[_HUSART_NUM];

Error_t HUSART_Init()
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	GPIO_Config_t GPIO_UART_TX=
	{
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

	GPIO_Config_t GPIO_UART_RX=
	{
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

	for(u8 Loc_Counter=0; Loc_Counter < _HUSART_NUM; Loc_Counter++)
	{
		GPIO_UART_TX.Port=HUSART_Config[Loc_Counter].TX_Port;
		GPIO_UART_TX.Pin=HUSART_Config[Loc_Counter].TX_Pin;
		GPIO_UART_RX.Port=HUSART_Config[Loc_Counter].RX_Port;
		GPIO_UART_RX.Pin=HUSART_Config[Loc_Counter].RX_Pin;
		Ret_HUSARTErrorStatus=GPIO_InitPinAF(&GPIO_UART_TX,HUSART_Config[Loc_Counter].TX_AF);
		Ret_HUSARTErrorStatus=GPIO_InitPinAF(&GPIO_UART_RX,HUSART_Config[Loc_Counter].RX_AF);
		Ret_HUSARTErrorStatus=USART_Init(HUSART_Config[Loc_Counter].USART_Config);

		switch(HUSART_Config[Loc_Counter].USART_Config.USART_ID)
		{
		case USART1:
			NVIC_EnableIRQ(NVIC_USART1);
			break;

		case USART2:
			NVIC_EnableIRQ(NVIC_USART2);
			break;

		case USART6:
			NVIC_EnableIRQ(NVIC_USART6);
			break;
		}
	}
	return Ret_HUSARTErrorStatus;
}


Error_t HUSART_SendBufferZC(USART_ReqBuffer_t TXBuffer)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_SendBufferZeroCopy(TXBuffer);

	return Ret_HUSARTErrorStatus;
}

Error_t HUSART_ReceiveBufferZC(USART_ReqBuffer_t RXBuffer)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_ReceiveBufferZeroCopy(RXBuffer);

	return Ret_HUSARTErrorStatus;
}

Error_t HUSART_SendByte(USART_IDs_t USART_ID, u8 Byte)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_SendByte(USART_ID,Byte);

	return Ret_HUSARTErrorStatus;
}
Error_t HUSART_ReceiveByte(USART_IDs_t USART_ID, u8* Byte)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_ReceiveByte(USART_ID,Byte);

	return Ret_HUSARTErrorStatus;
}
