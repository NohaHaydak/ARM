#ifndef MCAL_INCLUDES_USART_H_
#define MCAL_INCLUDES_USART_H_

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/
#include"stdlib.h"
#include"std_types.h"



/****************************************************************************************
 *                        	              MACROS                                         *
 ****************************************************************************************/

#define UASRT1  (volatile void * const)(0x40011000)
#define UASRT2  (volatile void * const)(0x40004400)
#define UASRT6  (volatile void * const)(0x40011400)


#define SYNCHMODE 

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/
typedef void (*TXCB_t)(void);
typedef void (*RXCB_t)(void);


/****************************************************************************************
 *                        	              APIs                                      *
 ****************************************************************************************/
void UASRT_Init(void * Copy_USARTNum);
u8 UASRT_SendByteZC(void* Copy_USARTNum, u8 Copy_Byte);
u8 UASRT_RecieveByteZC(void * Copy_USARTNum, u8* Add_Byte);
u8 UASRT_TXBufferAsynchZC(void* Copy_USARTNum, u8*Copy_Buffer, u16 Copy_length,TXCB_t Copy_Cb );
u8 UASRT_RXBufferAsynchZC(void* Copy_USARTNum, u8*Copy_Buffer, u16 Copy_length,RXCB_t Copy_Cb );


#endif /* MCAL_INCLUDES_USART_H_ */
