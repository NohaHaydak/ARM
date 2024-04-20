/*
 * LCD_CFG.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef HAL_INCLUDES_LCD_CFG_H_
#define HAL_INCLUDES_LCD_CFG_H_

/*
 * Select:
 * 1-LCD_DISPLAY_ON
 * 2-LCD_DISPLAY_OFF
 */
#define LCD_DISPLAY LCD_DISPLAY_ON
/*
 * Select:
 * 1-LCD_CURSOR_ON
 * 2-LCD_CURSOR_OFF
 */
#define LCD_CURSOR LCD_CURSOR_ON
/*
 * Select:
 * 1-LCD_BLINK_ON
 * 2-LCD_BLINK_OFF
 */
#define LCD_BLINK LCD_BLINK_OFF
/*
 * Select:
 * 1-LCD_INCREMENT
 * 2-LCD_DECREMENT
 */
#define LCD_INCREMENT_MODE LCD_INCREMENT
/*
 * Select:
 * 1-LCD_SHIFT_DISPLAY_ON
 * 2-LCD_SHIFT_DISPLAY_OFF
 */
#define LCD_SHIFT_DISPLAY LCD_SHIFT_DISPLAY_OFF
/*
 * Select:
 * 1-LCD_TWO_LINE_DISPLAY
 * 2-LCD_ONE_LINE_DISPLAY
 */
#define LCD_LINE_DISPLAY LCD_TWO_LINE_DISPLAY
/*
 * Select:
 * 1-LCD_5X7_CHAR_FONT
 * 2-LCD_5X10_CHAR_FONT
 */
#define LCD_FONT LCD_5X7_CHAR_FONT

#endif /* HAL_INCLUDES_LCD_CFG_H_ */