/*
 * Systick.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Noha
 */

#ifndef MCAL_INCLUDES_SYSTICK_H_
#define MCAL_INCLUDES_SYSTICK_H_

#include"stdio.h"
#include"../../LIB/std_types.h"
#include"systick_cfg.h"

#define STK_MODE_PERIODIC 1
#define STK_MODE_SINGLE   0

#define STATUS_NOK   0
#define INVALID_MODE 1
#define STATUS_OK    2

typedef void (*STK_CB_t) (void);

void MSTK_start(void);
u8 MSTK_init(u8 copy_STKmode);
void MSTK_stop(void);
void MSTK_setTime_ms(u16 copy_STKtime);
u8 MSTK_IsExpired(u8* Add_STKisExpired);
void MSTK_SetCallBack(STK_CB_t STK_CB);


#endif /* MCAL_INCLUDES_SYSTICK_H_ */
