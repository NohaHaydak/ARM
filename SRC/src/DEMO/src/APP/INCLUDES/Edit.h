/*
 * Edit.h
 *
 *  Created on: Apr 8, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef APP_INCLUDES_EDIT_H_
#define APP_INCLUDES_EDIT_H_
/*
typedef enum
{
	No_EditAction,
	UP_ARROW ,
	DOWN_ARROW,
	RIGHT_ARROW,
	LEFT_ARROW,
	INCREASE_BUTTON,
	DECREASE_BUTTON,
	OK
}EditPressedButton_t;
*/

typedef enum
{
	No_Edit_Action,
	Up_Arrow ,
	Down_Arrow,
	Right_Arrow,
	Left_Arrow,
	Increase_Button,
	Decrease_Button,
	Edit_Ok
}EditPressedButton_t;

/*
typedef enum
{
	EditOFF,
	EditON
}EditState_t;*/

typedef enum
{
	Edit_OFF,
	Edit_ON
}EditState_t;


#endif /* APP_INCLUDES_EDIT_H_ */
