
/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/
#include "stdlib.h"
#include"std_types.h"
#include "USART.h"
#include "USART_CFG.h"




/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

/**************Status register (USART_SR)**************
 * 1.
*/
#define CPE  0 /*Parity error*/
#define FE   1 /*Framing error*/
#define NF   2 /*Noise detected flag*/
#define ORE  3 /*Overrun error*/
#define IDLE 4 /*IDLE line detected*/
#define RXNE 5 /*Read data register not empty*/
#define TC   6 /*Transmission complete*/
#define TXE  7 /*Transmit data register empty*/
#define LBD  8 /*LIN break detection flag*/
#define CTS  9 /*CTS flag*/

/**************Data register (USART_DR)**************
 * 2.
*/
#define DR 0 /*[0-8] Data value*/
/*****************Baud rate register (USART_BRR)**************
 * 3.
*/
/**
 * Tx/Rx baud=fCK/(8 × (2 – OVER8) × USARTDIV)
*/

#define DIV_FRACTION 0 /*[0:3]fraction of USARTDIV*/
#define DIV_MANTISSA 4 /*[4:15]: mantissa of USARTDIV*/

/*USARTDIV is an unsigned fixed point number that is coded on the USART_BRR register.
• When OVER8=0, the fractional part is coded on 4 bits and programmed by the
DIV_fraction[3:0] bits in the USART_BRR register
• When OVER8=1, the fractional part is coded on 3 bits and programmed by the
DIV_fraction[2:0] bits in the USART_BRR register, and bit DIV_fraction[3] must be kept
cleared.*/


/*****************Control register 1 (USART_CR1)**************
 * 4.
*/

#define SBK    0  /*Send break*/
#define RWU    1  /*Receiver wakeup*/
#define RE     2  /*Receiver enable*/
#define TE     3  /*Transmitter enable*/
#define IDLEIE 4  /*IDLE interrupt enable*/
#define RXNEIE 5  /*RXNE interrupt enable*/
#define TCIE   6  /*Transmission complete interrupt enable*/
#define TXEIE  7  /*TXE interrupt enable*/
#define PEIE   8  /*PE interrupt enable*/
#define PS     9  /*Parity selection*/
#define PCE    10 /*Parity control enable*/
#define WAKE   11 /*Wakeup method*/
#define M      12 /*Word length*/
#define UE     13 /*USART enable*/
#define OVER8  15 /*Oversampling mode*/



#define UE_ENABLEMASK 0x2000
#define TE_ENABLE_MASK 0x8
#define RE_ENABLE_MASK 0x4
#define TXEIE_CLR_MASK 0xFF7F
#define TXEIE_ENABLE_MASK 0x80
#define TXEIE_DISABLE_MASK 0x80

/*****************Control register 2 (USART_CR2)**************
 * 5.
*/
#define ADD   0  /*[0-3]Address of the USART node*/
#define LBDL  5  /*lin break detection length*/
#define LBDIE 6  /* LIN break detection interrupt enable*/
#define LBCL  8  /*Last bit clock pulse*/
#define CBHA  9  /*Clock phase*/
#define CPOL  10 /*Clock polarity*/
#define CLKEN 11 /*Clock enable*/
#define STOP  12 /*[12-13]STOP bits*/
#define LINEN 14 /*LIN mode enable*/


#define STOP_BIT_CLR_MASK 0xCFFF
/*****************Control register 3 (USART_CR3)**************
 * 6.
*/
#define EIE     0  /* Error interrupt enable*/
#define IREN    1  /* IrDA mode enable*/
#define IRLP    2  /*IrDA low-power*/
#define HDSEL   3  /*Half-duplex selection*/
#define NACK    4  /*Smartcard NACK enable*/
#define SCEN    5  /*Smartcard mode enable*/
#define DMAR    6  /*DMA enable receiver*/
#define DMAT    7  /*DMA enable transmitter*/
#define RTSE    8  /*RTS enable*/
#define CTSE    9  /*CTS enable*/ 
#define CTSIE   10 /*CTS interrupt enable*/
#define ONEBITT 11 /*One sample bit method enable*/

/*****************Guard time and prescaler register (USART_GTPR)**************
 * 7.
*/
#define PSC 0 /*[0-7]Prescaler value*/
#define GT  5 /*[8-15]Guard time value*/



/*********************bytes*********************/
#define B0 0
/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/
typedef struct
{
    u32 USART_SR;
    u32 USART_DR;
    u32 USART_BRR;
    u32 USART_CR1;
    u32 USART_CR2;
    u32 USART_CR3;
    u32 USART_GTPR;
}USART_t;
typedef struct 
{
    u8* Data;
    u32 Position;
    u32 Size;
    
}Buffer_t;
typedef struct 
{
    Buffer_t Buffer;
    TXCB_t CB;
    
}TXReq_t;

typedef struct 
{
    Buffer_t Buffer;
    TXCB_t CB;
}RXReq_t;

typedef enum
{
    TXREQ_STATAE_READY,
    TXREQ_STATAE_BUSY
}TXReqState_t;
typedef enum
{
    RXREQ_STATAE_READY,
    RXREQ_STATAE_BUSY
}RXReqState_t;
/****************************************************************************************
 *                        	     static functions decleration                           *
 ****************************************************************************************/
static TXCB_t TXCb;
static RXCB_t RXCb;
static TXReq_t TXReq;
static RXReq_t RXReq;
TXReqState_t G_TXReqState=TXREQ_STATAE_READY;
RXReqState_t G_RXReqState=RXREQ_STATAE_READY;
static void TX_CallBack(void);
static void RX_CallBack(void);

void UASRT_Init(void * Copy_USARTNum)
{
    u32 Loc_BuadRate=0;
    u32 Loc_DIV_MANTISSA=0;
    u32 Loc_DIV_FRACTION=0;
    /*USART Enable*/
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=UE_ENABLEMASK;
    /*Ensble TE*/
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=TE_ENABLE_MASK;
    /*Enable RE*/
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=RE_ENABLE_MASK;
    /*In Reciever The start bit detection sequence is the same when oversampling by 16 or by 8.*/
    #if OVER_SAMPLING==OVER_8
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=OVER8;
    #elif OVER_SAMPLING==OVER_16
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=OVER16;
    #endif
    /*WORD length 8 or 9 bits*/
    #if DATABITS_NUM==EIGHT_BIT_DATA
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=EIGHT_BIT_DATA;
    #elif DATABITS_NUM==NINE_BIT_DATA
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=NINE_BIT_DATA;
    #endif
    #if PARITY_CONTROL_STATUS==PARITY_CONTROL_DISABLED
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=PARITY_CONTROL_DISABLED;
    #elif PARITY_CONTROL_STATUS ==PARITY_CONTROL_ENABLED_EVEN
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=PARITY_CONTROL_ENABLED_EVEN;
    #elif PARITY_CONTROL_STATUS ==PARITY_CONTROL_ENABLED_ODD
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=PARITY_CONTROL_ENABLED_ODD;
    #endif
    /*Num of Stop bits*/
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR2&=STOP_BIT_CLR_MASK;
    #if STOP_BIT_NUM==ONE_STOP_BIT
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR2|=ONE_STOP_BIT;
    #elif STOP_BIT_NUM==TWO_STOP_BIT
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR2|=TWO_STOP_BIT;
    #elif STOP_BIT_NUM==HALF_STOP_BIT
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR2|=HALF_STOP_BIT;
    #endif
    /*Buad Rate*/
    Loc_BuadRate=((u64)CLK_FREQ*1000)/(8 * (2 -(OVER_SAMPLING>>OVER8)) * BUAD_RATE_VALUE);
    Loc_DIV_MANTISSA=(Loc_BuadRate/1000)<<DIV_MANTISSA;
    Loc_DIV_FRACTION=((Loc_BuadRate%1000)* 8 *(2-(OVER_SAMPLING>>OVER8)));
    //Loc_DIV_FRACTION=(Loc_BuadRate%1000)* 8;
    if ((Loc_DIV_FRACTION%1000)>=500)
    {
        Loc_DIV_FRACTION=(Loc_DIV_FRACTION/1000)+1;
    }
    else
    {
        Loc_DIV_FRACTION/=1000;
    }
    #if OVER_SAMPLING==OVER_16
    if (Loc_DIV_FRACTION>=8)
    {
        Loc_DIV_MANTISSA+=(1<<DIV_MANTISSA);
        Loc_DIV_FRACTION=0;
    }
    else
    {
    }
    #endif

    ((volatile USART_t * const)Copy_USARTNum)->USART_BRR=(Loc_DIV_MANTISSA|Loc_DIV_FRACTION);


}
u8 UASRT_SendByteZC(void * Copy_USARTNum, u8 Copy_Byte)
{
    u8 Loc_TXE=0;
    Loc_TXE=(((volatile USART_t * const)Copy_USARTNum)->USART_SR>>TXE)&&0x1;
    /*Loc_TXE=(((volatile USART_t * const)Copy_USARTNum)->USART_SR>>TC)&&0x1;
    if(Loc_TC==0)
    {
        ((volatile USART_t * const)Copy_USARTNum)->USART_DR=Copy_Byte;
    }
    */  
    if(Loc_TXE==0)
    {
        ((volatile USART_t * const)Copy_USARTNum)->USART_DR=Copy_Byte;
    }
}
u8 UASRT_RecieveByteZC(void * Copy_USARTNum, u8* Add_Byte)
{
    u8 Loc_RXNE=0;
    Loc_RXNE=(((volatile USART_t * const)Copy_USARTNum)->USART_SR>>RXNE)&&0x1;
    /*Loc_TXE=(((volatile USART_t * const)Copy_USARTNum)->USART_SR>>RC)&&0x1;
    if(Loc_RC==0)
    {
        *Add_Byte=((volatile USART_t * const)Copy_USARTNum)->USART_DR;
    }
    */  
    if(Loc_RXNE==0)
    {
        *Add_Byte=((volatile USART_t * const)Copy_USARTNum)->USART_DR;
    }
}
u8 UASRT_TXBufferAsynchZC(void* Copy_USARTNum, u8*Copy_Buffer, u16 Copy_length,TXCB_t Copy_Cb )
{
    u8 Loc_TXE=0;
    Loc_TXE=(((volatile USART_t * const)Copy_USARTNum)->USART_SR>>TXE)&&0x1;
    /*Loc_TXE=(((volatile USART_t * const)Copy_USARTNum)->USART_SR>>TC)&&0x1;*/
    
    /*if(Loc_TC==0)
    {
        TXReq.Buffer.Position++;
    }
    */  
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1&=TXEIE_CLR_MASK;
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=TXEIE_ENABLE_MASK;
    if(G_TXReqState==TXREQ_STATAE_READY)
    {
        TXReq.Buffer.Data=Copy_Buffer;
        TXReq.Buffer.Size=Copy_length;
        G_TXReqState=TXREQ_STATAE_BUSY;
        TXReq.CB=Copy_Cb;
        /*Send first Byte to start intterupt and step into handler*/
        ((volatile USART_t * const)Copy_USARTNum)->USART_DR=Copy_Buffer[B0];
        TXReq.Buffer.Position++;       
    }
    
}

u8 UASRT_RXBufferAsynchZC(void* Copy_USARTNum, u8*Copy_Buffer, u16 Copy_length,RXCB_t Copy_Cb )
{
    u8 Loc_RXNE=0;
    Loc_RXNE=(((volatile USART_t * const)UASRT1)->USART_SR>>RXNE)&&0x1;
    /*Loc_TXE=(((volatile USART_t * const)Copy_USARTNum)->USART_SR>>TC)&&0x1;*/
    
    /*if(Loc_TC==0)
    {
        TXReq.Buffer.Position++;
    }
    */  
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1&=TXEIE_CLR_MASK;
    ((volatile USART_t * const)Copy_USARTNum)->USART_CR1|=TXEIE_ENABLE_MASK;
    if(G_TXReqState==RXREQ_STATAE_READY)
    {
        RXReq.Buffer.Data=Copy_Buffer;
        RXReq.Buffer.Size=Copy_length;
        G_RXReqState=RXREQ_STATAE_BUSY;
        RXReq.CB=Copy_Cb;
    }
    
}
void USART1_IRQHandler(void)
{
    u8 Loc_TXE=0;
    u8 Loc_RXNE=0;
    Loc_TXE=(((volatile USART_t * const)UASRT1)->USART_SR>>TXE)&&0x1;
    Loc_RXNE=(((volatile USART_t * const)UASRT1)->USART_SR>>RXNE)&&0x1;
    if(Loc_TXE)
    {
        if (TXReq.Buffer.Position<TXReq.Buffer.Size)
        {
            ((volatile USART_t * const)UASRT1)->USART_DR=TXReq.Buffer.Data[TXReq.Buffer.Position];
            TXReq.Buffer.Position++;
        }
        

        else if( TXReq.Buffer.Position== TXReq.Buffer.Size)
        {
            G_TXReqState=TXREQ_STATAE_READY;
            if(TXReq.CB)
            {
                TXReq.CB();
            }
             
        }

    }
    if(!Loc_RXNE)
    {
        if (RXReq.Buffer.Position<RXReq.Buffer.Size)
        {
            RXReq.Buffer.Data[RXReq.Buffer.Position]=((volatile USART_t * const)UASRT1)->USART_DR;
            RXReq.Buffer.Position++;
        }
        

        else if( RXReq.Buffer.Position== RXReq.Buffer.Size)
        {
            G_RXReqState=RXREQ_STATAE_READY;
            if(RXReq.CB)
            {
                RXReq.CB();
            }
             
        }

    }
    
}
void USART2_IRQHandler(void)
{
    u8 Loc_TXE=0;
    u8 Loc_RXNE=0;
    Loc_TXE=(((volatile USART_t * const)UASRT2)->USART_SR>>TXE)&&0x1;
    Loc_RXNE=(((volatile USART_t * const)UASRT2)->USART_SR>>TXE)&&0x1;
    if(Loc_TXE)
    {
        if (TXReq.Buffer.Position<TXReq.Buffer.Size)
        {
            ((volatile USART_t * const)UASRT2)->USART_DR=TXReq.Buffer.Data[TXReq.Buffer.Position];
            TXReq.Buffer.Position++;
        }
        

        if( TXReq.Buffer.Position== TXReq.Buffer.Size)
        {
            G_TXReqState=TXREQ_STATAE_READY;
            if(TXReq.CB)
            {
                TXReq.CB();
            }
             
        }

    }
    if(!Loc_RXNE)
    {
        if (RXReq.Buffer.Position<RXReq.Buffer.Size)
        {
            RXReq.Buffer.Data[RXReq.Buffer.Position]=((volatile USART_t * const)UASRT2)->USART_DR;
            RXReq.Buffer.Position++;
        }
        

        if( RXReq.Buffer.Position== RXReq.Buffer.Size)
        {
            G_RXReqState=RXREQ_STATAE_READY;
            if(RXReq.CB)
            {
                RXReq.CB();
            }
             
        }

    }
}
void USART6_IRQHandler(void)
{
    u8 Loc_TXE=0;
    u8 Loc_RXNE=0;
    Loc_TXE=(((volatile USART_t * const)UASRT6)->USART_SR>>TXE)&&0x1;
    Loc_RXNE=(((volatile USART_t * const)UASRT6)->USART_SR>>TXE)&&0x1;
    if(Loc_TXE)
    {
        if (TXReq.Buffer.Position<TXReq.Buffer.Size)
        {
            ((volatile USART_t * const)UASRT6)->USART_DR=TXReq.Buffer.Data[TXReq.Buffer.Position];
            TXReq.Buffer.Position++;
        }
        

        if( TXReq.Buffer.Position== TXReq.Buffer.Size)
        {
            G_TXReqState=TXREQ_STATAE_READY;
            if(TXReq.CB)
            {
                TXReq.CB();
            }
             
        }

    }
    if(!Loc_RXNE)
    {
        if (RXReq.Buffer.Position<RXReq.Buffer.Size)
        {
            RXReq.Buffer.Data[RXReq.Buffer.Position]=((volatile USART_t * const)UASRT1)->USART_DR;
            RXReq.Buffer.Position++;
        }
        

        if( RXReq.Buffer.Position== RXReq.Buffer.Size)
        {
            G_RXReqState=RXREQ_STATAE_READY;
            if(RXReq.CB)
            {
                RXReq.CB();
            }
             
        }

    }
}
