/*
 * LCD.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Noha
 */
#include "../INCLUDES/LCD.h"
#include "string.h"
#include "../../MCAL/INCLUDES/GPIO.h"
#define PERIODICITY 1

#define FUNCTION_SET    0
#define DISPLAY_CONTROL 1
#define DISPLAY_CLR     2
#define ENTRY_MODE      3


#define REQ_BUFFER 		 10

extern GPIO_pin_t G_GPIO_pin[CONTROL_PINS];
extern GPIO_pin_t LCD_arrStructDataPins[LDC_DATA_PINS];
typedef void(* LCDcb_t) (void);

typedef enum
{
	USER_REQ_TYPE_NULL,
	USER_REQ_TYPE_WRITE_STRING,
	USER_REQ_TYPE_SET_CURSSOR,
	USER_REQ_TYPE_CLR,
}userReqtype_t;


typedef enum
{
	USER_REQ_READY,
	USER_REQ_BUSY,
	USER_REQ_DONE //when all HW reqs/ bits are sent (we send string as char by char)
}userReqState_t;

typedef enum
{
	BUFFER_EMPTY,
	BUFFERED,
	BUFFER_FULL
}BufferState_t;

typedef struct
{
	const char* string;
	userReqState_t state;
	u32 length;
	userReqtype_t type;
	BufferState_t bufferState;
}userReq_t;



typedef enum
{
	INIT_STATE,
	OPERATION_STATE
}LCD_state_t;

typedef struct
{
	u8 COL_NUM;
	u8 ROW_NUM;
}LCD_POSITION_t;

typedef struct
{
	u8 CURRENT_POSITION;
	LCD_POSITION_t CURSSOR_POS;
	LCDcb_t LCD_CB;
}LCD_write_t;

u8 G_LCD_col=0;
u8 G_LCD_Row=0;
u8 G_enableBit=LCD_DISABLED;
userReq_t GuserReq[REQ_BUFFER];
LCD_write_t G_LCD_write;
LCD_state_t G_LCD_state=INIT_STATE;
static u8 G_reqCounter=0;
static u8 G_CurrBuffer=0;



static void LCD_WriteProcess(void);
static void LCD_ClrScreenProcess(void);
static void LCD_enuGotoDDRAM_XYProcess(void);
static void LCD_WriteData(u8 Copy_u8Data);
static void LCD_WriteCommand(u8 Copy_u8Command);
static void LCD_EnablePin(u8 Copy_LCDenablePin);
static void LCD_HandlingReqBuffer(void);
//each 1ms as runnable law 2ms gwa init hghir if >=
void LCD_task(void)
{
	switch(G_LCD_state)
	{
		case INIT_STATE:
			LCD_Init();
			break;
		case OPERATION_STATE:
			switch(GuserReq[G_CurrBuffer].state)
			{
				case USER_REQ_BUSY:
					switch(GuserReq[G_CurrBuffer].type)
					{
						case USER_REQ_TYPE_NULL:
							break;
						case USER_REQ_TYPE_WRITE_STRING:
							LCD_WriteProcess();
							break;
						case USER_REQ_TYPE_SET_CURSSOR:
							LCD_enuGotoDDRAM_XYProcess();
							break;
						case USER_REQ_TYPE_CLR:
							LCD_ClrScreenProcess();

					}
					break;

					case USER_REQ_DONE:
						LCD_HandlingReqBuffer();
						break;
					case USER_REQ_READY:
						break;



			}


			break;

	}

}
void LCD_Init(void)
{	static u32 Loc_sec;
	static u8 Loc_state=0;
	u8 Loc_functionSet=0;
	u8 Loc_displayOn=0;
	u8 loc_entryMode=0;
	Loc_sec+=PERIODICITY;
	switch(Loc_state)
	{
		case FUNCTION_SET:
			if(Loc_sec>=1)
			{
			#if LCD_MODE == EIGHT_BIT

				/*......check on num of lines chosen.......*/
				#if NUM_OF_LINES==2
				/*......check on font size chosen.......*/
					#if CHAR_SIZE== 57
					//FUNCTION_SET_2LINE_5X7F 0b00111000
					Loc_functionSet=FUNCTION_SET_2LINE_5X7F;
				/*......check on font size chosen.......*/
					#elif CHAR_SIZE== 510
					 //FUNCTION_SET_2LINE_5X10F 0b00111100
					LCD_enuWriteCommand(FUNCTION_SET_2LINE_5X10F);
					#endif
				/*......check on num of lines chosen.......*/
				#elif NUM_OF_LINES==1
				/*......check on font size chosen.......*/
					#if CHAR_SIZE== 57
					 //FUNCTION_SET_1LINE_5X7F 0b00110000
					LCD_enuWriteCommand(FUNCTION_SET_1LINE_5X7F);
				/*......check on font size chosen.......*/
					#elif CHAR_SIZE== 510
					//FUNCTION_SET_1LINE_5X10F 0b00110100
					LCD_enuWriteCommand(FUNCTION_SET_1LINE_5X10F);
					#endif
				#endif

				#elif LCD_MODE == FOUR_BIT

					LCD_enuWriteCommand(0b00000010);
					/*......check on num of lines chosen.......*/
					#if NUM_OF_LINES==2
					/*......check on font size chosen.......*/
						#if CHAR_SIZE== 57
						//FUNCTION_SET_2LINE_5X7F  0b00001000
						LCD_enuWriteCommand(FOUR_BIT_FUNCTION_SET_2LINE_5X7F);
						/*......check on font size chosen.......*/
						#elif CHAR_SIZE== 510
						//FUNCTION_SET_2LINE_5X10F  0b00001100
						LCD_enuWriteCommand(FOUR_BIT_FUNCTION_SET_2LINE_5X10F);
						#endif
					/*......check on num of lines chosen.......*/
					#elif NUM_OF_LINES==1
						/*......check on font size chosen.......*/
						#if CHAR_SIZE== 57
						//FUNCTION_SET_1LINE_5X7F 0b00000000
						LCD_enuWriteCommand(FOUR_BIT_FUNCTION_SET_1LINE_5X7F);
						/*......check on font size chosen.......*/
						#elif CHAR_SIZE== 510
						//FUNCTION_SET_1LINE_5X10F 0b00000100
						LCD_enuWriteCommand(FOUR_BIT_FUNCTION_SET_1LINE_5X10F);
						#endif
					#endif


				#endif

				if(G_enableBit==LCD_DISABLED)
				{
					LCD_WriteCommand(Loc_functionSet);
					G_enableBit=LCD_ENABLED;
					LCD_EnablePin(G_enableBit);
				}
				else if(G_enableBit==LCD_ENABLED)
				{
					G_enableBit=LCD_DISABLED;
					LCD_EnablePin(G_enableBit);
					Loc_state=DISPLAY_CONTROL;
					Loc_sec=0;
				}
				else
				{

				}
			}

			break;

		case DISPLAY_CONTROL:
			if(Loc_sec>=1)
			{
				/*.............display is on.......*/
					#if DISPLAY == DISPLAY_ON
						/*...........cursor is displayed.......*/
						#if CURSOR == CURSOR_ON
							/*...........cursor is blinking.......*/
							#if CURSOR_BLINK==CURSOR_BLINK_ON
								// DISPLAY_CURSOR_BLINK_ALL_ON 0b00001111
								Loc_displayOn=DISPLAY_CURSOR_BLINK_ALL_ON;
								LCD_WriteCommand(Loc_displayOn);
								/*...........cursor is not blinking.......*/
							#elif CURSOR_BLINK==CURSOR_BLINK_OFF
							// DISPLAY_CURSOR_ON_BLINK_OFF 0b00001110
								Loc_displayOn=DISPLAY_CURSOR_ON_BLINK_OFF;
								LCD_WriteCommand(Loc_displayOn);
							#endif
						/*...........cursor is not displayed.......*/
						#elif CURSOR == CURSOR_OFF
							// DISPLAY_ON_CURSOR_OFF 0b00001100
							Loc_displayOn=DISPLAY_ON_CURSOR_OFF;
							LCD_WriteCommand(Loc_displayOn);
						#endif
					/*.............display is off.......*/
					#elif DISPLAY == DISPLAY_OFF
						// DISPLAY_ALL_OFF 0b00001000
						Loc_displayOn=DISPLAY_ALL_OFF;
						LCD_WriteCommand(Loc_displayOn);

					#endif

					if(G_enableBit==LCD_DISABLED)
					{
						LCD_WriteCommand(Loc_displayOn);
						G_enableBit=LCD_ENABLED;
						LCD_EnablePin(G_enableBit);
					}
					else if(G_enableBit==LCD_ENABLED)
					{
						G_enableBit=LCD_DISABLED;
						LCD_EnablePin(G_enableBit);
						Loc_state=DISPLAY_CLR;
						Loc_sec=0;
					}
					else
					{

					}

			}
			else
			{

			}
			break;

		case DISPLAY_CLR:
			if(Loc_sec>=1)
			{

				if(G_enableBit==LCD_DISABLED)
				{
					LCD_WriteCommand(DISPLAY_CLEAR);
					G_enableBit=LCD_ENABLED;
					LCD_EnablePin(G_enableBit);
				}
				else if(G_enableBit==LCD_ENABLED)
				{
					G_enableBit=LCD_DISABLED;
					LCD_EnablePin(G_enableBit);
					Loc_state=ENTRY_MODE;
					Loc_sec=0;
				}

			}
			else
			{

			}
			break;

		case ENTRY_MODE:
			if(Loc_sec>=2)
			{
				/*...........writing eng (from left to right)...*/
					#if ENTRY_DIRECTION == TO_THE_RIGHT
						/*....................shifting the screen is enabled................*/
						#if DISPLAY_SHIFT == DISPLAY_SHIFT_ON
							loc_entryMode=ENTRY_TO_THE_RIGHT_SHIFT_ON;
							LCD_WriteCommand(loc_entryMode);
						/*....................shifting the screen is disabled................*/
						#elif DISPLAY_SHIFT == DISPLAY_SHIFT_OFF
							loc_entryMode=ENTRY_TO_THE_RIGHT_SHIFT_OFF;
							LCD_WriteCommand(loc_entryMode);
						#endif

					/*...........writing arabic (from right to left)...*/
					#elif ENTRY_DIRECTION == TO_THE_LEFT
						#if DISPLAY_SHIFT == DISPLAY_SHIFT_ON
						/*....................shifting the screen is enabled................*/
							loc_entryMode=ENTRY_TO_THE_LEFT_SHIFT_ON;
							LCD_WriteCommand(loc_entryMode);
						/*....................shifting the screen is disabled................*/
						#elif DISPLAY_SHIFT == DISPLAY_SHIFT_OFF
							loc_entryMode=ENTRY_TO_THE_LEFT_SHIFT_OFF;
							LCD_WriteCommand(loc_entryMode);
						#endif

					#endif

					if(G_enableBit==LCD_DISABLED)
					{
						LCD_WriteCommand(loc_entryMode);
						G_enableBit=LCD_ENABLED;
						LCD_EnablePin(G_enableBit);
					}
					else if(G_enableBit==LCD_ENABLED)
					{
						G_enableBit=LCD_DISABLED;
						LCD_EnablePin(G_enableBit);
						G_LCD_state=OPERATION_STATE;
						GuserReq[G_CurrBuffer].state=USER_REQ_READY;
						Loc_sec=0;
					}

			}
			else
			{

			}
			break;


	}

}

void LCD_WriteString_Asynch(char* Copy_pchPattern )
{
	GuserReq[G_CurrBuffer].length=strlen(Copy_pchPattern);
	if(G_LCD_state==OPERATION_STATE&&GuserReq[G_CurrBuffer].state==USER_REQ_READY)
	{
		GuserReq[G_CurrBuffer].state=USER_REQ_BUSY;
		GuserReq[G_CurrBuffer].type=USER_REQ_TYPE_WRITE_STRING ;
		GuserReq[G_CurrBuffer].string=Copy_pchPattern;
	}
	else
	{

	}
}

void LCD_enuGotoDDRAM_XY_Asynch(u8 Copy_u8Row, u8 Copy_u8Col)
{
	if(G_LCD_state==OPERATION_STATE&&GuserReq[G_CurrBuffer].state==USER_REQ_READY)
	{
		GuserReq[G_CurrBuffer].state=USER_REQ_BUSY;
		GuserReq[G_CurrBuffer].type=USER_REQ_TYPE_SET_CURSSOR ;
		G_LCD_write.CURSSOR_POS.COL_NUM=Copy_u8Col;
		G_LCD_write.CURSSOR_POS.ROW_NUM=Copy_u8Row;
	}
	else
	{

	}
}

void LCD_ClrScreen_Asynch(void)
{
	if(G_LCD_state==OPERATION_STATE&&GuserReq[G_CurrBuffer].state==USER_REQ_READY)
	{
		GuserReq[G_CurrBuffer].state=USER_REQ_BUSY;
		GuserReq[G_CurrBuffer].type=USER_REQ_TYPE_CLR ;
	}
	else
	{

	}

}

void LCD_WriteCB(LCDcb_t LCDcb)
{
	if(LCDcb)
	{
		G_LCD_write.LCD_CB=LCDcb;
	}
}

void LCD_enuGotoDDRAM_XYProcess(void)
{
	static u8 local_DdramAdress=0;
	static u8 local_DdramCommand=0;
	switch(GuserReq[G_CurrBuffer].state)
	{
		case USER_REQ_READY:
			if(G_enableBit==LCD_DISABLED)
			{

				if(G_LCD_write.CURSSOR_POS.ROW_NUM==0&&G_LCD_write.CURSSOR_POS.COL_NUM<VALID_COL_RANGE)
				{
					/*.......................if we chose first row , the base address we start counting from is 0x00 and local_DdramAdress is according to col num..............*/
					local_DdramAdress=G_LCD_write.CURSSOR_POS.COL_NUM;
				}
				else if(G_LCD_write.CURSSOR_POS.COL_NUM>=VALID_COL_RANGE)
				{
					G_LCD_write.CURSSOR_POS.ROW_NUM=1;
					/*.....if we chose second row , the base address we start counting from is 0x40 and local_DdramAdress is according to the sum of both col and row num........*/
					local_DdramAdress=SEC_ROW_START+G_LCD_write.CURSSOR_POS.COL_NUM;
				}
				/*........................set bit 7 of  DdramCommand by 1 to send the address to DDRAM...........................*/
				local_DdramCommand=(SET_AC_MASK)|local_DdramAdress;
				LCD_WriteCommand(local_DdramCommand);
				/*...............generate pulses to switch on the enable pin.............*/
				G_enableBit=LCD_ENABLED;
				LCD_EnablePin(G_enableBit);
			}
			else
			{
				/*...............generate pulses to switch on the enable pin.............*/
				G_enableBit=LCD_DISABLED;
				LCD_EnablePin(G_enableBit);
				GuserReq[G_CurrBuffer].state=USER_REQ_DONE;
			}

			break;

		case USER_REQ_DONE:
			GuserReq[G_CurrBuffer].state=USER_REQ_READY;
			GuserReq[G_CurrBuffer].type=USER_REQ_TYPE_NULL;
			break;
		case USER_REQ_BUSY:
			break;
		default:
			break;

		}

}
void LCD_WriteProcess(void)
{
	switch(GuserReq[G_CurrBuffer].state)
	{
		case USER_REQ_READY:
			if(G_enableBit==LCD_DISABLED)
			{

				if(G_LCD_write.CURRENT_POSITION==GuserReq[G_CurrBuffer].length)
				{
					GuserReq[G_CurrBuffer].state=USER_REQ_DONE;
					G_LCD_write.CURRENT_POSITION=0;

				}
				else
				{
					 LCD_WriteData(GuserReq[G_CurrBuffer].string[G_LCD_write.CURRENT_POSITION]);
					 G_LCD_write.CURRENT_POSITION++;
					 /*if(G_LCD_write.CURSSOR_POS.COL_NUM<VALID_COL_RANGE)
					 {
						 G_LCD_write.CURSSOR_POS.COL_NUM+=G_LCD_write.CURRENT_POSITION;
						 //go with cursor there
					 }*/
				G_enableBit=LCD_ENABLED;
				LCD_EnablePin(G_enableBit);

				}
			}
			else if(G_enableBit==LCD_ENABLED)
			{
				G_enableBit=LCD_DISABLED;
				LCD_EnablePin(G_enableBit);

			}
			else
			{

			}
			break;

		case USER_REQ_DONE:
			GuserReq[G_CurrBuffer].state=USER_REQ_READY;
			GuserReq[G_CurrBuffer].type=USER_REQ_TYPE_NULL;
			//irq++
			break;
		case USER_REQ_BUSY:
			break;
		default:
			break;

	}


}


void LCD_ClrScreenProcess(void)
{
	static u32 Loc_sec;
	switch(GuserReq[G_CurrBuffer].state)
		{
			case USER_REQ_READY:
				if(G_enableBit==LCD_DISABLED)
				{
					LCD_WriteCommand(DISPLAY_CLEAR);
					if(Loc_sec==2)
					{
						G_enableBit=LCD_ENABLED;
						LCD_EnablePin(G_enableBit);
						Loc_sec=0;
					}
					else
					{
						Loc_sec+=PERIODICITY;
					}


				}
				else if(G_enableBit==LCD_ENABLED)
				{
					G_enableBit=LCD_DISABLED;
					LCD_EnablePin(G_enableBit);
					GuserReq[G_CurrBuffer].state=USER_REQ_DONE;

				}
				else
				{

				}
				break;

			case USER_REQ_DONE:
				GuserReq[G_CurrBuffer].state=USER_REQ_READY;
				GuserReq[G_CurrBuffer].type=USER_REQ_TYPE_NULL;
				//irq++
				break;
			case USER_REQ_BUSY:
				break;
			default:
				break;

		}

}
void LCD_WriteData(u8 Copy_u8Data)
{

	for(u8 itr=0; itr<CONTROL_PINS ;itr++)
	{
		GPIO_initPin(G_GPIO_pin[itr]);

	}
	/*.....................use RS (register select) control pin to receive data.......*/
	GPIO_setPinValue(G_GPIO_pin[PINRS].GPIONum,G_GPIO_pin[PINRS].pinNum,LCD_RS_DATA);
	/*.....................use R/W (read write) control pin to to decide read or write.......*/
	GPIO_setPinValue(G_GPIO_pin[PINRW].GPIONum,G_GPIO_pin[PINRW].pinNum,LCD_WRITE);

	/*.....................send data over data pins..........*/
	#if LCD_MODE == EIGHT_BIT

	for(u8 itr=0 ; itr< EIGHT_BIT;itr++)
	{
		u8 Loc_pinValue=0;
		GPIO_initPin(LCD_arrStructDataPins[itr]);
		Loc_pinValue=0x01&(Copy_u8Data>>itr);
		GPIO_setPinValue(LCD_arrStructDataPins[itr].GPIONum,LCD_arrStructDataPins[itr].pinNum,Loc_pinValue);
	}
	#elif LCD_MODE == FOUR_BIT
	u8 Local_u8DataHighNibble=GET_HIGH_NIB(Copy_u8Data);
	u8 Local_u8DataLowNibble=GET_LOW_NIB(Copy_u8Data);
	for(u8 itr=0 ; itr<4;itr++)
	{
		DIO_enuSetPinConfiguration(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,DIO_OUTPUT);
		u8 local_logicalValue=GET_BIT(Local_u8DataHighNibble,itr);
		DIO_enuSetPin(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,local_logicalValue);
	}
	/*...............generate pulses to switch on the enable pin to receive the sent data/ command.............*/
	DIO_enuSetPin(PORTC,PIN2,LCD_ENABLE_ON);
	_delay_ms(1);
	DIO_enuSetPin(PORTC,PIN2,LCD_ENABLE_OFF);
	_delay_ms(1);
	for(u8 itr=0 ; itr<4;itr++)
	{
		DIO_enuSetPinConfiguration(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,DIO_OUTPUT);
		u8 local_logicalValue=GET_BIT(Local_u8DataLowNibble,itr);
		DIO_enuSetPin(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,local_logicalValue);
	}
	#endif
	/*...............generate pulses to switch on the enable pin.............*/
	/*GPIO_setPinValue(G_GPIO_pin[PINENABLE].GPIONum,G_GPIO_pin[PINENABLE].pinNum,LCD_ENABLE_ON);
	_delay_ms(1);
	GPIO_setPinValue(G_GPIO_pin[PINENABLE].GPIONum,G_GPIO_pin[PINENABLE].pinNum,LCD_ENABLE_OFF);
	_delay_ms(1);*/
}

void LCD_WriteCommand(u8 Copy_u8Command)
{

	for(u8 itr=0; itr<CONTROL_PINS ;itr++)
	{
		GPIO_initPin(G_GPIO_pin[itr]);

	}
	/*.....................use RS (register select) control pin to receive data.......*/
	GPIO_setPinValue(G_GPIO_pin[PINRS].GPIONum,G_GPIO_pin[PINRS].pinNum,LCD_RS_COMMAND);
	/*.....................use R/W (read write) control pin to to decide read or write.......*/
	GPIO_setPinValue(G_GPIO_pin[PINRW].GPIONum,G_GPIO_pin[PINRW].pinNum,LCD_WRITE);

	/*.....................send data over data pins..........*/

	#if LCD_MODE == EIGHT_BIT

	for(u8 itr=0 ; itr< EIGHT_BIT;itr++)
	{
		u8 Loc_pinValue=0;
		GPIO_initPin(LCD_arrStructDataPins[itr]);
		Loc_pinValue=0x01&(Copy_u8Command>>itr);
		GPIO_setPinValue(LCD_arrStructDataPins[itr].GPIONum,LCD_arrStructDataPins[itr].pinNum,Loc_pinValue);
	}
	#elif LCD_MODE == FOUR_BIT
	u8 Local_u8DataHighNibble=GET_HIGH_NIB(Copy_u8Data);
	u8 Local_u8DataLowNibble=GET_LOW_NIB(Copy_u8Data);
	for(u8 itr=0 ; itr<4;itr++)
	{
		DIO_enuSetPinConfiguration(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,DIO_OUTPUT);
		u8 local_logicalValue=GET_BIT(Local_u8DataHighNibble,itr);
		DIO_enuSetPin(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,local_logicalValue);
	}
	/*...............generate pulses to switch on the enable pin to receive the sent data/ command.............*/
	DIO_enuSetPin(PORTC,PIN2,LCD_ENABLE_ON);
	_delay_ms(1);
	DIO_enuSetPin(PORTC,PIN2,LCD_ENABLE_OFF);
	_delay_ms(1);
	for(u8 itr=0 ; itr<4;itr++)
	{
		DIO_enuSetPinConfiguration(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,DIO_OUTPUT);
		u8 local_logicalValue=GET_BIT(Local_u8DataLowNibble,itr);
		DIO_enuSetPin(LCD_arrStructDataPins[itr].LCD_DataPort,LCD_arrStructDataPins[itr].LCD_DataPin,local_logicalValue);
	}
	#endif

}

void LCD_HandlingReqBuffer(void)
{
	GuserReq[G_CurrBuffer].bufferState=BUFFER_EMPTY;
	for(G_reqCounter=0;G_reqCounter<REQ_BUFFER;G_reqCounter++)
	{
		if(GuserReq[G_reqCounter].bufferState==BUFFERED)
		{
			break;
		}
	}
	if(G_reqCounter==REQ_BUFFER)
	{
		GuserReq[G_CurrBuffer].bufferState=BUFFER_FULL;
		GuserReq[G_CurrBuffer].type=USER_REQ_TYPE_NULL;
		G_CurrBuffer=0;

	}
	else
	{
		G_CurrBuffer=G_reqCounter; // Update current buffer index
		GuserReq[G_CurrBuffer].state=USER_REQ_READY; // Set request state to request start
		if (G_CurrBuffer==REQ_BUFFER) // Check if current buffer index equals LCD buffer size
		{
			G_CurrBuffer=0; // Reset current buffer index
		}
	}
}
void LCD_EnablePin(u8 Copy_LCDenablePin)
{
	GPIO_setPinValue(G_GPIO_pin[PINENABLE].GPIONum,G_GPIO_pin[PINENABLE].pinNum,Copy_LCDenablePin);
}
