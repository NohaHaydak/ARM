/*
 * LCD.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Noha
 */
#include "../INCLUDES/LCD.h"

#define PERIODICITY 1

#define FUNCTION_SET    0
#define DISPLAY_CONTROL 1
#define DISPLAY_CLR     2
#define ENTRY_MODE      3


typedef enum
{
	INIT_STATE,
	OPERATION_STATE,
	OFF_STATE
}LCD_state_t;

LCD_state_t G_LCD_state=INIT_STATE;
u8 LCD_task(void);
//each 1ms as runnable law 2ms gwa init hghir if >=
u8 LCD_task(void)
{
	switch(G_LCD_state)
	{
		case INIT_STATE:
			u8 LCD_enuInit(void);
			break;
	}

}
u8 LCD_enuInit(void)
{	static u32 Loc_sec;
	static u8 Loc_state=0;
	switch(Loc_state)
	{
		Loc_sec+=PERIODICITY;
		case FUNCTION_SET:
			if(Loc_sec==35)
				{
			#if LCD_MODE == EIGHT_BIT

				/*......check on num of lines chosen.......*/
				#if NUM_OF_LINES==2
				/*......check on font size chosen.......*/
					#if CHAR_SIZE== 57
					//FUNCTION_SET_2LINE_5X7F 0b00111000
					LCD_enuWriteCommand(FUNCTION_SET_2LINE_5X7F);
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
					Loc_state=DISPLAY_CONTROL;
				}
			else
			{
				//do nothing
			}
			break;

		case DISPLAY_CONTROL:
			if(Loc_sec==1)
			{
				/*.............display is on.......*/
					#if DISPLAY == DISPLAY_ON
						/*...........cursor is displayed.......*/
						#if CURSOR == CURSOR_ON
							/*...........cursor is blinking.......*/
							#if CURSOR_BLINK==CURSOR_BLINK_ON
								// DISPLAY_CURSOR_BLINK_ALL_ON 0b00001111
								LCD_enuWriteCommand(DISPLAY_CURSOR_BLINK_ALL_ON);
								/*...........cursor is not blinking.......*/
							#elif CURSOR_BLINK==CURSOR_BLINK_OFF
							// DISPLAY_CURSOR_ON_BLINK_OFF 0b00001110
								LCD_enuWriteCommand(DISPLAY_CURSOR_ON_BLINK_OFF);
							#endif
						/*...........cursor is not displayed.......*/
						#elif CURSOR == CURSOR_OFF
							// DISPLAY_ON_CURSOR_OFF 0b00001100
							LCD_enuWriteCommand(DISPLAY_ON_CURSOR_OFF);
						#endif
					/*.............display is off.......*/
					#elif DISPLAY == DISPLAY_OFF
						// DISPLAY_ALL_OFF 0b00001000
						LCD_enuWriteCommand(DISPLAY_ALL_OFF);

					#endif
					Loc_state=DISPLAY_CLR;
			}
			else
			{

			}
			break;

		case DISPLAY_CLR:
			if(Loc_sec==1)
			{
				LCD_enuWriteCommand(DISPLAY_CLEAR);
				Loc_state=ENTRY_MODE;
			}
			else
			{

			}
			break;

		case ENTRY_MODE:
			if(Loc_sec==2)
			{
				/*...........writing eng (from left to right)...*/
					#if ENTRY_DIRECTION == TO_THE_RIGHT
						/*....................shifting the screen is enabled................*/
						#if DISPLAY_SHIFT == DISPLAY_SHIFT_ON
							LCD_enuWriteCommand(ENTRY_TO_THE_RIGHT_SHIFT_ON);
						/*....................shifting the screen is disabled................*/
						#elif DISPLAY_SHIFT == DISPLAY_SHIFT_OFF
							LCD_enuWriteCommand(ENTRY_TO_THE_RIGHT_SHIFT_OFF);
						#endif

					/*...........writing arabic (from right to left)...*/
					#elif ENTRY_DIRECTION == TO_THE_LEFT
						#if DISPLAY_SHIFT == DISPLAY_SHIFT_ON
						/*....................shifting the screen is enabled................*/
							LCD_enuWriteCommand(ENTRY_TO_THE_LEFT_SHIFT_ON);
						/*....................shifting the screen is disabled................*/
						#elif DISPLAY_SHIFT == DISPLAY_SHIFT_OFF
							LCD_enuWriteCommand(ENTRY_TO_THE_LEFT_SHIFT_OFF);
						#endif

					#endif
					G_LCD_state=OPERATION_STATE;
			}
			else
			{

			}
			break;


	}

}


