#ifndef MCAL_INCLUDES_USART_CFG_H_
#define MCAL_INCLUDES_USART_CFG_H_







#define EIGHT_BIT_DATA 0x0000
#define NINE_BIT_DATA  0x1000
#define DATABITS_NUM   EIGHT_BIT_DATA


#define PARITY_CONTROL_ENABLED_EVEN  0x400
#define PARITY_CONTROL_ENABLED_ODD   0x600
#define PARITY_CONTROL_DISABLED      0x000
#define PARITY_CONTROL_STATUS        PARITY_CONTROL_DISABLED


#define ONE_STOP_BIT  0x0000
#define HALF_STOP_BIT 0x1000
#define TWO_STOP_BIT  0x2000
#define STOP_BIT_NUM  ONE_STOP_BIT

#define OVER_8         0x0000
#define OVER_16        0X8000
#define OVER_SAMPLING  OVER_8

#define CLK_FREQ        16000000
#define BUAD_RATE_VALUE 9600






#endif /* MCAL_INCLUDES_USART_CFG_H_ */