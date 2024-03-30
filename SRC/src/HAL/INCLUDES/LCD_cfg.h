/*
 * LCD_cfg.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Noha
 */

#ifndef HAL_INCLUDES_LCD_CFG_H_
#define HAL_INCLUDES_LCD_CFG_H_

#define LCD_MODE  EIGHT_BIT
#define EIGHT_BIT 8
#define FOUR_BIT 4

/*.........................................................function set ...................................................*/

#define NUM_OF_LINES 2
#define CHAR_SIZE 57

/*.....................................................display on/off control..........................................................*/

#define DISPLAY DISPLAY_ON
#define DISPLAY_ON 1
#define DISPLAY_OFF 0

#define CURSOR CURSOR_ON
#define CURSOR_ON 1
#define CURSOR_OFF 0

#define CURSOR_BLINK CURSOR_BLINK_ON
#define CURSOR_BLINK_ON 1
#define CURSOR_BLINK_OFF 0

/*.............................................................Entry mode set.........................................................*/
#define ENTRY_DIRECTION  TO_THE_RIGHT
#define TO_THE_RIGHT 1
#define TO_THE_LEFT 0

#define DISPLAY_SHIFT DISPLAY_SHIFT_OFF
#define DISPLAY_SHIFT_ON 1
#define DISPLAY_SHIFT_OFF 0

#define VALID_ROW_RANGE 2
#define VALID_COL_RANGE 16




#endif /* HAL_INCLUDES_LCD_CFG_H_ */
